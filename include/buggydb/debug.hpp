/**
 * @file debug.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

//#define BUGGY_DEBUG

void print_buffer(int nesting_level, uint8_t *buffer, unsigned long size)
{
#if defined(BUGGY_DEBUG)
#define MAX_NUMBER_IN_LINE 8

    char *nesting_string = (char *)calloc(4 * nesting_level + 1, 1);
    memset(nesting_string, ' ', 4 * nesting_level);

    if (size > 0)
    {
        printf("%s%2x ", nesting_string, buffer[0]);
        for (int i = 1; i < size; ++i)
        {
            if (i % MAX_NUMBER_IN_LINE == 0)
            {
                printf("\n%s%2x ", nesting_string, buffer[i]);
            }
            else
            {
                printf("%2x ", buffer[i]);
            }
        }
        printf("\n");
    }
#endif // BUGGY_DEBUG
}
