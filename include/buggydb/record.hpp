#pragma once
#include <cstdint>
#include <string>
#include <cstddef>
#include <buggydb/value_interface.hpp>

namespace buggydb
{
    struct record
    {
    public:
        char key[128];
        bool offline;
        value_interface *value;
        record *next;

        static record *create(std::string key, value_interface *value, record *next = nullptr);
    };
} // namespace buggydb
