#pragma once
#include <cstdint>
#include <cstddef>

namespace buggydb
{
    typedef struct table_meta
    {
        char name[32];
        size_t length; // count of records
        size_t byte_size;// size of all records
    } table_meta;
} // namespace buggydb
