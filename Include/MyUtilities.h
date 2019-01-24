/**
 * utilities file of C language
 *
 * @file MyUtilities.h
 * @brief C utilitis library
 * @author Shouji, Igarashi
 *
 * (c) 2018 Shouji, Igarashi.
 */

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

unsigned char copyBitByte(const unsigned short * chkBit, const unsigned char * resultBit, size_t size, unsigned short target);
unsigned short copyBitWord(const unsigned short * chkBit, const unsigned short * resultBit, size_t size, unsigned short target);
unsigned long copyBitDWord(const unsigned short * chkBit, const unsigned long * resultBit, size_t size, unsigned short target);

size_t copyByte(union Byte dst[], const union Byte src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyWord(union Word dst[], const union Word src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyDWord(union DWord dst[], const union DWord src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);

void SimpleAlloc_init(unsigned long buff[], size_t count);
void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size);

struct DataRecordCtrol
{
    union DWord *           buff;
    const unsigned short *  ids;
    size_t                  dwordCount;
    size_t                  wordCount;
    size_t                  byteCount;
    size_t                  dwordMaxIDs;
    size_t                  wordMaxIDs;
    size_t                  byteMaxIDs;
};
void RecCtrl_init(struct DataRecordCtrol * obj, union DWord * buff, const unsigned short * ids, const unsigned short * cnt, size_t DwMax, size_t WdMax, size_t ByMax);
unsigned char RecCtrl_dataSize(struct DataRecordCtrol * obj, unsigned short key);
void RecCtrl_copy(struct DataRecordCtrol * dst, struct DataRecordCtrol * src);
union DWord * RecCtrl_get(struct DataRecordCtrol * obj, unsigned short key);

struct RecStreamCtrl
{
    struct DataRecordCtrol * rec;
    const unsigned short *   fmt;
    size_t                   idx;
    size_t                   cnt;
    size_t                   max;
    unsigned char            pos;
    unsigned char            dsz;
};
void RecStreamCtrl_init(struct RecStreamCtrl * stm, struct DataRecordCtrol * rec, const unsigned short * fmt, size_t fmtCnt);
size_t RecStreamCtrl_Size(struct RecStreamCtrl * stm);
void RecStreamCtrl_in(struct RecStreamCtrl * stm, unsigned char data);
unsigned char RecStreamCtrl_get(struct RecStreamCtrl * stm);


#endif
