#ifndef __MyUtilities_h__
#define __MyUtilities_h__

#include <stdlib.h>

/* 16/32 bit Architecture */
/* unsigned char  :  8 bit */
/* unsigned short : 16 bit */
/* unsigned long  : 32 bit */
/* float          : 32 bit */
/* unsigned int   : 16/32 bit */
union Byte
{
    unsigned char   data;
    unsigned char   byte;
    signed char     val;
};

union Word
{
    unsigned short  data;
    union Byte      byte[2];
    unsigned short  word;
    signed short    val;
};

union DWord
{
#if __x86_64__
    unsigned int    data;
#else
    unsigned long   data;
#endif
    union Byte      byte[4];
    union Word      word[2];
#if __x86_64__
    unsigned int   dword;
    signed int     val;
#else
    unsigned long   dword;
    signed long     val;
#endif
    float           value;
};

size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned char target);
size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target);
size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned long target);
size_t getIndexArrayCString(const char * array[], size_t count, const char * target);

size_t copyByte(union Byte dst[], const union Byte src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyWord(union Word dst[], const union Word src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyDWord(union DWord dst[], const union DWord src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);

void SimpleAlloc_init(unsigned long buff[], size_t count);
void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size);


#endif
