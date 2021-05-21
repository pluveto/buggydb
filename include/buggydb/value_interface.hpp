#pragma once

#include <cstddef>

namespace buggydb
{
    class value_interface
    {
    private:
    public:
        virtual size_t size() = 0;
        virtual char *serialize() = 0;
        static void * deserialize(char * buffer);
    };
}