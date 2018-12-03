#include "MyUtilities.h"
#include <string.h>

#define getIndexArray(T) \
{ \
    size_t len, top = 0; \
    for(len=count; 0 < len; len >>=1) \
    { \
        size_t        mid = top + (len>>1); \
        T val = array[mid]; \
        if(val == target) \
        { \
            return mid; \
        } \
        if(val < target) \
        { \
            top = mid; \
            if(1 & len) \
            { \
                mid = top + (len>>1); \
                val = array[mid]; \
                if(val == target) \
                { \
                    return mid; \
                } \
            } \
        } \
    } \
}

size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned short target)
{
    //getIndexArray(unsigned char, array, count, target);
    getIndexArray(unsigned char);
    return count;
}

size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target)
{
    //getIndexArray(unsigned short, array, count, target);
    getIndexArray(unsigned short);
    return count;
}

size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned short target)
{
    //getIndexArray(unsigned long, array, count, target);
    getIndexArray(unsigned long);
    return count;
}

size_t getIndexArrayCString(const char * array[], size_t count, const char * target)
{
    size_t len, top = 0;
    for(len=count; 0 < len; len >>=1)
    {
        size_t mid = top + (len>>1);
        int    cmp = strcmp(target, array[mid]);
        if(cmp == 0)
        {
            return mid;
        }
        if(0 < cmp)
        {
            top = mid;
            if(1 & len)
            {
                mid = top + (len>>1);
                cmp = strcmp(target, array[mid]);
                if(cmp == 0)
                {
                    return mid;
                }
            }
        }
    }
    return count;
}
