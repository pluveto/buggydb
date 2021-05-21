
/**
 * @file buggydb.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <buggydb/buggydb.hpp>

#include <iostream>
#include <fstream>

namespace buggydb
{
    void buggydb::base_dir(std::string base_dir)
    {
        this->_base_dir = base_dir;
    }

    btable *buggydb::create_table(std::string table_name)
    {
        /**
         * @brief TODO: delete when release table
         * 
         */
        btable *t = new btable();
        this->_tables[table_name] = t;
        t->name(table_name);
        this->save_table(t);
        return t;
    }

    btable *buggydb::table(std::string table_name)
    {
        auto t = this->_tables.find(table_name);
        if (t == this->_tables.end())
        {
            return nullptr;
        }
        return t->second;
    }

    bool buggydb::save_table(btable *table)
    {
        std::string filename = this->_base_dir + "/" + table->name() + ".bin";
        std::ofstream outfile;

        printf("saving %s...\n", table->name().c_str());

        outfile.open(filename, std::ios::out | std::ios::trunc);
        auto table_buffer = table->serialize();
        outfile.write((char *)table_buffer, table->serial_size());
        delete table_buffer;
        outfile.close();
        return true;
    }

    std::string buggydb::get_last_err()
    {
        return this->_last_error_msg;
    }

} // namespace buggydb
