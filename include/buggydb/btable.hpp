/**
 * @file btable.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <buggydb/table_meta.hpp>
#include <buggydb/record.hpp>
#include <buggydb/value_interface.hpp>

namespace buggydb
{
    class btable
    {
    private:
        table_meta *_table_meta;
        record *_records; // first is head
        uint8_t *serialize_records();

    public:
        btable();
        void name(std::string name);
        size_t insert(std::string key, value_interface *value);
        std::string name();
        size_t serial_size();
        size_t record_length();
        uint8_t *serialize();
    };

} // namespace buggydb
