/**
 * @file empty_value.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <cstddef>
#include <buggydb/value_interface.hpp>

namespace buggydb
{
    class empty_value : public value_interface
    {
    private:
    public:
        size_t size()
        {
            return 0;
        }
        char *serialize()
        {
            return nullptr;
        }
        static void *deserialize(char *buffer)
        {
            return nullptr;
        }
    };
}