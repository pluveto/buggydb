/**
 * @file btable.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <buggydb/debug.hpp>
#include <buggydb/btable.hpp>

#include <cstring>

#include <buggydb/empty_value.hpp>

namespace buggydb
{

    btable::btable()
    {
        this->_table_meta = new table_meta;
        memset(this->_table_meta->name, 0, sizeof(this->_table_meta->name));
        this->_table_meta->length = 0;
        this->_table_meta->byte_size = 0;
        this->_records = record::create("___head", new empty_value(), nullptr);
    }

    void btable::name(std::string name)
    {
        strcpy(this->_table_meta->name, name.c_str());
    }

    std::string btable::name()
    {
        return std::string(this->_table_meta->name);
    }

    size_t btable::serial_size()
    {
        size_t meta_size = sizeof(*this->_table_meta);
        size_t body_size = this->_table_meta->byte_size;
        u_int8_t prefix[] = {0xa8, 0xac, 0x49, 0x75};
        /**
         * +-------------------------------------------------------------+
         * |  meta_size  |  meta | body_size | body
         * +-------------------------------------------------------------+
         */
        size_t table_byte_size = sizeof(prefix) + meta_size + sizeof(body_size) + body_size;
        return table_byte_size;
    }

    size_t btable::record_length()
    {
        return this->_table_meta->length;
    }

    size_t btable::insert(std::string key, value_interface *value)
    {
        printf("insert with key %s, size = %zu\n", key.c_str(), value->size());
        record *last = this->_records;
        while (last->next != nullptr)
        {
            last = last->next;
        }
        auto new_record = last->next = record::create(key, value);
        this->_table_meta->byte_size += sizeof(new_record->key);
        this->_table_meta->byte_size += value->size();
        this->_table_meta->length++;
        printf("byte_size = %zu\n", this->_table_meta->byte_size);
        return 0;
    }

    uint8_t *btable::serialize_records()
    {
        size_t body_size = this->_table_meta->byte_size;
        if (body_size == 0)
        {
            printf("empty body.\n");
            return nullptr;
        }
        /**
         * @brief Deleted in btable::serialize()
         * 
         */
        uint8_t *all_buf = new uint8_t[body_size]; // to be released in serialize
        //TODO: implement serialize_records
        record *cur_rec = this->_records;
        size_t cursor = 0;
        while (nullptr != cur_rec)
        {
            size_t rec_val_size = cur_rec->value->size();
            char *rec_buf = cur_rec->value->serialize();

            printf("memcpy for %s\n", cur_rec->key);

            memcpy(all_buf + cursor, cur_rec->key, sizeof(cur_rec->key));
            cursor += sizeof(cur_rec->key);

            memcpy(all_buf + cursor, rec_buf, rec_val_size);
            cursor += rec_val_size;

            cur_rec = cur_rec->next;
        }
        printf("body buffer:\n");
        print_buffer(1, all_buf, body_size);
        return all_buf;
    }
    uint8_t *btable::serialize()
    {
        printf("serializing %s...\n", this->name().c_str());

        size_t meta_size = sizeof(*this->_table_meta);
        size_t body_size = this->_table_meta->byte_size;
        u_int8_t prefix[] = {0xa8, 0xac, 0x49, 0x75};
        /**
         * +-------------------------------------------------------------+
         * |  meta_size  |  meta | body_size | body
         * +-------------------------------------------------------------+
         */
        size_t table_byte_size = sizeof(prefix) + meta_size + sizeof(body_size) + body_size;
        /**
         * @brief Deleted in buggydb::save_table(btable *table)
         * 
         */
        uint8_t *buffer = new uint8_t[table_byte_size];
        uint8_t *body_buffer = this->serialize_records();

        size_t cursor = 0;

        // write "pluveto"
        memcpy(buffer + cursor, prefix, sizeof(prefix));
        cursor += sizeof(prefix);

        // write table meta
        memcpy(buffer + cursor, this->_table_meta, meta_size);
        cursor += meta_size;

        // write body size
        memcpy(buffer + cursor, &body_size, sizeof(body_size));
        cursor += sizeof(body_size);
        if (nullptr != body_buffer)
        {
            // write body
            memcpy(buffer + cursor, body_buffer, body_size);
            cursor += sizeof(body_size);
            delete body_buffer;
        }
        printf("table buffer:\n");
        print_buffer(1, buffer, table_byte_size);

        return buffer;
    }
} // namespace buggydb
