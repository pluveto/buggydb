/**
 * @file record.cpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <cstdint>
#include <string>
#include <cstring>
#include <cstddef>
#include <buggydb/record.hpp>

namespace buggydb
{
    record *record::create(std::string key, value_interface *value, record* next)
    {
        /**
         * @brief TODO: delete when release table
         * 
         */
        auto r = new record();
        r->offline = false;
        strcpy(r->key, key.c_str());
        r->value = value;
        return r;
    }

} // namespace buggydb
