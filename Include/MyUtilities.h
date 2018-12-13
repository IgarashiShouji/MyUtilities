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
    unsigned char   byte[2];
    unsigned short  word;
    signed short    val;
};

union DWord
{
    unsigned long   data;
    unsigned char   byte[4];
    union Word      word[2];
    unsigned long   dword;          /* 64 bit Architecture is 8 byte size       */
    signed long     val;            /* 64 bit Architecture is 8 byte size       */
    float           value;
};

size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned short target);
size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target);
size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned short target);
size_t getIndexArrayCString(const char * array[], size_t count, const char * target);

void SimpleAlloc_init(unsigned long buff[], size_t count);
void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size);


#endif
