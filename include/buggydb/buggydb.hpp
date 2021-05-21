/**
 * @file buggydb.hpp
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
#include <unordered_map>
#include <buggydb/btable.hpp>
namespace buggydb
{
    class buggydb
    {
    private:
        std::string _base_dir;
        std::string _last_error_msg;
        std::unordered_map<std::string, btable *> _tables;

    public:
        void base_dir(std::string base_dir);
        btable *create_table(std::string table_name);
        btable *table(std::string table_name);
        bool save_table(btable *table);
        bool drop_table(btable *table);
        std::string get_last_err();
        buggydb() = default;
        ~buggydb() = default;
    };

} // namespace buggydb
