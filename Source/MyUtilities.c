/**
 * utilities file of C language
 *
 * @file MyUtilities.h
 * @brief C utilitis library
 * @author Shouji, Igarashi
 *
 * (c) 2018 Shouji, Igarashi.
 */

/**
 * @mainpage MyUtilities
 * This software is embedded library.
 *
 * @section main_sec C languages libraries
 * C languages libraries.
 *
 * @subsection main_subsec Array Utilities
 * Array list operation utilities.
 *
 * @par index find on array list.
 * find index on sorted array list.
 *
 * @par index copy Array List
 * copy array to array by ID list.
 *
 * @section second_sec C++ languages libraries
 * C++ languages libraries.
 *
 * - SVG Sample
 * @image html "../sample.svg"
 *
 * - PUML Sample
 * @startuml
 * hide footbox
 * skinparam monochrome true
 * 
 * actor "System" as sys
 * participant "Object 1" as obj1
 * participant "Object 2" as obj2
 * participant "Object 3" as obj3
 * participant "Object 4" as obj4
 * participant "Object 5" as obj5
 * 
 * loop Start Event
 *   sys -> obj1: new(unsgiend int, unsigned int)
 *   activate obj1
 *   obj1 --> sys
 *   deactivate obj1
 *   sys -> obj2: append()
 *   activate obj2
 *     obj2 -> obj3 : append()
 *     activate obj3
 *     obj3 --> obj2
 *     deactivate obj3
 *     obj2 -> obj4 : append()
 *     activate obj4
 *     obj4 --> obj2
 *     deactivate obj4
 *   obj2 --> sys
 *   deactivate obj2
 * end
 * activate obj2
 *   obj2 -> obj3 : initialize()
 *   activate obj3
 *     alt
 *       obj3 -> obj5 : save()
 *       activate obj5
 *       obj5 --> obj3
 *       deactivate obj5
 *     else
 *     end
 *   obj3 --> obj2
 *   deactivate obj3
 *   obj2 -> obj4 : initialize()
 *   activate obj4
 *   obj4 --> obj2
 *   deactivate obj4
 * deactivate obj2
 * 
 * @enduml
 *
 */

#include "MyUtilities.h"
#include <string.h>

#define _getIndexArray(T) \
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

size_t getIndexArray(const size_t * array, size_t count, const size_t target)
{
    _getIndexArray(size_t);
    return count;
}

size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned char target)
{
    _getIndexArray(unsigned char);
    return count;
}

size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target)
{
    _getIndexArray(unsigned short);
    return count;
}

size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned long target)
{
    _getIndexArray(unsigned long);
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

size_t getFirstIndex(const unsigned char * const list[], const unsigned char list_sz[], const size_t count, const size_t pos, const unsigned char target)
{
    size_t result = 0;
    unsigned char  val = list[0][pos];
    if(val != target)
    {
        size_t top, len;
        result = count;
        for(top = 0, len = count; (top < count) && (0 < len); len >>= 1)
        {
            size_t mid = top + (len >> 1);
            val = list[mid][pos];
            if(pos < list_sz[mid])
            {
                if(val == target)
                {
                    result = mid;
                }
                else if(val < target)
                {
                    top = mid;
                    if(1 & len)
                    {
                        mid = top + (len >> 1);
                        val = list[mid][pos];
                        if(val == target)
                        {
                            result = mid;
                        }
                    }
                }
                else
                {
                }
            }
        }
    }
    return result;
}

size_t getListSize(const unsigned char * const list[], const unsigned char list_sz[], unsigned short count, unsigned char pos, unsigned char target)
{
    size_t result = 0;
    if(list[0][pos] == target)
    {
        if(list[count-1][pos] != target)
        {
            size_t top = 0, size = 0, len;
            for(len = count; 0 < len; len >>= 1)
            {
                size_t        mid = top + (len >> 1);
                unsigned char val = list[mid][pos];
                if(val == target)
                {
                    top    = mid;
                    result = mid + 1;
                    if(1 & len)
                    {
                        mid = top + (len >> 1);
                        val = list[mid][pos];
                        if(val == target)
                        {
                            result = mid + 1;
                        }
                    }
                }
            }
        }
        else
        {
            result = count;
        }
    }
    return result;
}

struct Range getRangeOfListByte(const unsigned char * const list[], const unsigned char list_sz[], const size_t count, const size_t pos, const unsigned char target)
{
    struct Range res;
    res.idx = getFirstIndex(&(list[0]), &(list_sz[0]), count, pos, target);
    if(res.idx < count)
    {
        res.cnt = getListSize(&(list[res.idx]), &(list_sz[res.idx]), (count - res.idx), pos, target);
    }
    else
    {
        res.idx = 0;
        res.cnt = 0;
    }
    return res;
}

unsigned char getIndexNoBitMask8(unsigned char target,  const unsigned char * tbl_mask, const unsigned char * tbl_true, const unsigned char * tbl_false, size_t tbl_cnt)
{
    unsigned char result = 0xff;
    if(0 != target)
    {
        unsigned char node = 0, idx;
        for(idx = 0; (idx < tbl_cnt) && (node < tbl_cnt); idx ++)
        {
            if(target & tbl_mask[node])
            {
                if(0xff == tbl_true[node])
                {
                    result = node;
                    break;
                }
                node = tbl_true[node];
            }
            else
            {
                node = tbl_false[node];
                while((0xff != tbl_true[node]) && (0xff == tbl_false[node]))
                {
                    node = tbl_true[node];
                }
                if((0xff == tbl_true[node]) && (0xff == tbl_false[node]))
                {
                    result = node;
                    break;
                }
            }
        }
    }
    return result;
}

unsigned char getIndexNoBitMask16(unsigned short target,  const unsigned short * tbl_mask, const unsigned char * tbl_true, const unsigned char * tbl_false, size_t tbl_cnt)
{
    unsigned char result = 0xff;
    if(0 != target)
    {
        unsigned char node = 0, idx;
        for(idx = 0; (idx < tbl_cnt) && (node < tbl_cnt); idx ++)
        {
            if(target & tbl_mask[node])
            {
                if(0xff == tbl_true[node])
                {
                    result = node;
                    break;
                }
                node = tbl_true[node];
            }
            else
            {
                node = tbl_false[node];
                while((0xff != tbl_true[node]) && (0xff == tbl_false[node]))
                {
                    node = tbl_true[node];
                }
                if((0xff == tbl_true[node]) && (0xff == tbl_false[node]))
                {
                    result = node;
                    break;
                }
            }
        }
    }
    return result;
}

unsigned char getBitIndex8(unsigned char target)
{
#if 1
                                        /*      [0],  [1],  [2],  [3],  [4],  [5],  [6],  [7],  [8],  [9], [10] */
    static const unsigned char  tbl_mask[] = { 0x0f, 0x03, 0x01, 0x02, 0x04, 0x08, 0x30, 0x10, 0x20, 0x40, 0x80 };
    static const unsigned char  tbl_no[]   = { 0xff, 0xff,    0,    1,    2,    3, 0xff,    4,    5,    6,    7 };
    static const unsigned char  tbl_true[] = {    1,    2, 0xff, 0xff, 0xff, 0xff,    7, 0xff, 0xff, 0xff, 0xff };
    static const unsigned char  tbl_false[]= {    6,    4,    3, 0xff,    5, 0xff,    9,    8, 0xff,   10, 0xff };
    unsigned char result = 0xff;

    if(0 != target)
    {
        unsigned char node = 0, idx;
        for(idx = 0; (idx < (sizeof(tbl_mask)/sizeof(tbl_mask[0]))) && (node < (sizeof(tbl_mask)/sizeof(tbl_mask[0]))); idx ++)
        {
            if(target & tbl_mask[node])
            {
                if(0xff == tbl_true[node])
                {
                    result = tbl_no[node];
                    break;
                }
                node = tbl_true[node];
            }
            else
            {
                node = tbl_false[node];
            }
        }
    }
#else
    static const unsigned char  tbl_mask[15]  = {/*  0 */(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80), /*  1 */(0x01|0x02|0x04|0x08), /*  2 */(0x01|0x02), /*  3 */(0x01), /*  4 */(0x02), /*  5 */(0x04|0x08), /*  6 */(0x04), /*  7 */(0x08), /*  8 */(0x10|0x20|0x40|0x80), /*  9 */(0x10|0x20), /* 10 */(0x10), /* 11 */(0x20), /* 12 */(0x40|0x80), /* 13 */(0x40), /* 14 */(0x80)};
    static const unsigned char  tbl_true[15]  = {   1,    2,    3, 0xFF, 0xFF,    6, 0xFF, 0xFF,    9,   10, 0xFF, 0xFF,   13, 0xFF, 0xFF};
    static const unsigned char  tbl_false[15] = {0xFF,    8,    5,    4, 0xFF, 0xFF,    7, 0xFF, 0xFF,   12,   11, 0xFF, 0xFF,   14, 0xFF};
    static const unsigned char  tbl_no[15]    = {0xFF, 0xFF, 0xFF,    0,    1, 0xFF,    2,    3, 0xFF, 0xFF,    4,    5, 0xFF,    6,    7};
    unsigned char idx, result = 0xff;

    idx = getIndexNoBitMask8(target, tbl_mask, tbl_true, tbl_false, __Count(tbl_mask));
    if(idx < __Count(tbl_mask))
    {
        result = tbl_no[idx];
    }
#endif
    return result;
}

unsigned char getBitIndex16(unsigned short target)
{
#if 1
                                            /*    [0],    [1],    [2],    [3],   [4],    [5],     [6],    [7],    [8],    [9],   [10],   [11],   [12],   [13],   [14],   [15],   [16],   [17],   [18],   [19],   [20],   [21],   [22] */
    static const unsigned short tbl_mask[] = { 0x00ff, 0x000f, 0x0003, 0x0001, 0x0002, 0x0004, 0x0008, 0x0030, 0x0010, 0x0020, 0x0040, 0x0080, 0x0f00, 0x0300, 0x0100, 0x0200, 0x0400, 0x0800, 0x3000, 0x1000, 0x2000, 0x4000, 0x8000 };
    static const unsigned char  tbl_no[]   = {   0xff,   0xff,   0xff,      0,      1,      2,      3,   0xff,      4,      5,      6,      7,   0xff,   0xff,      8,      9,     10,     11,   0xff,     12,     13,     14,     15 };
    static const unsigned char  tbl_true[] = {      1,      2,      3,   0xff,   0xff,   0xff,   0xff,      8,   0xff,   0xff,   0xff,   0xff,     13,     14,   0xff,   0xff,   0xff,   0xff,     19,   0xff,   0xff,   0xff,   0xff };
    static const unsigned char  tbl_false[]= {     12,      7,      5,      4,   0xff,      6,   0xff,     10,      9,   0xff,     11,   0xff,     18,     16,     15,   0xff,     17,   0xff,     21,     20,   0xff,     22,   0xff };
    unsigned char result = 0xff;

    if(0 != target)
    {
        unsigned char node = 0, idx;
        for(idx = 0; (idx < __Count(tbl_mask)) && (node < __Count(tbl_mask)); idx ++)
        {
            if(target & tbl_mask[node])
            {
                if(0xff == tbl_true[node])
                {
                    result = tbl_no[node];
                    break;
                }
                node = tbl_true[node];
            }
            else
            {
                node = tbl_false[node];
            }
        }
    }
#else
    static const unsigned short tbl_mask[31]  = {/*  0 */(0x0001|0x0002|0x0004|0x0008|0x0010|0x0020|0x0040|0x0080|0x0100|0x0200|0x0400|0x0800|0x1000|0x2000|0x4000|0x8000), /*  1 */(0x0001|0x0002|0x0004|0x0008|0x0010|0x0020|0x0040|0x0080), /*  2 */(0x0001|0x0002|0x0004|0x0008), /*  3 */(0x0001|0x0002), /*  4 */(0x0001), /*  5 */(0x0002), /*  6 */(0x0004|0x0008), /*  7 */(0x0004), /*  8 */(0x0008), /*  9 */(0x0010|0x0020|0x0040|0x0080), /* 10 */(0x0010|0x0020), /* 11 */(0x0010), /* 12 */(0x0020), /* 13 */(0x0040|0x0080), /* 14 */(0x0040), /* 15 */(0x0080), /* 16 */(0x0100|0x0200|0x0400|0x0800|0x1000|0x2000|0x4000|0x8000), /* 17 */(0x0100|0x0200|0x0400|0x0800), /* 18 */(0x0100|0x0200), /* 19 */(0x0100), /* 20 */(0x0200), /* 21 */(0x0400|0x0800), /* 22 */(0x0400), /* 23 */(0x0800), /* 24 */(0x1000|0x2000|0x4000|0x8000), /* 25 */(0x1000|0x2000), /* 26 */(0x1000), /* 27 */(0x2000), /* 28 */(0x4000|0x8000), /* 29 */(0x4000), /* 30 */(0x8000)};
    static const unsigned char  tbl_true[31]  = {   1,    2,    3,    4, 0xFF, 0xFF,    7, 0xFF, 0xFF,   10,   11, 0xFF, 0xFF,   14, 0xFF, 0xFF,   17,   18,   19, 0xFF, 0xFF,   22, 0xFF, 0xFF,   25,   26, 0xFF, 0xFF,   29, 0xFF, 0xFF};
    static const unsigned char  tbl_false[31] = {0xFF,   16,    9,    6,    5, 0xFF, 0xFF,    8, 0xFF, 0xFF,   13,   12, 0xFF, 0xFF,   15, 0xFF, 0xFF,   24,   21,   20, 0xFF, 0xFF,   23, 0xFF, 0xFF,   28,   27, 0xFF, 0xFF,   30, 0xFF};
    static const unsigned char  tbl_no[31]    = {0xFF, 0xFF, 0xFF, 0xFF,    0,    1, 0xFF,    2,    3, 0xFF, 0xFF,    4,    5, 0xFF,    6,    7, 0xFF, 0xFF, 0xFF,    8,    9, 0xFF,   10,   11, 0xFF, 0xFF,   12,   13, 0xFF,   14,   15};
    unsigned char idx, result = 0xff;

    idx = getIndexNoBitMask16(target, tbl_mask, tbl_true, tbl_false, __Count(tbl_mask));
    if(idx < __Count(tbl_mask))
    {
        result = tbl_no[idx];
    }
#endif
    return result;
}

unsigned char getBitIndex32(union DWord target)
{
    unsigned char result = 0xff;
    if(0 != target.data)
    {
        unsigned char idx;
        for(idx = 0; idx < 2; idx ++)
        {
            result = getBitIndex16(target.words[idx].data);
            if(0xff != result)
            {
                result += idx * 16;
                break;
            }
        }
    }
    return result;
}

#define copyBit() \
{ \
    size_t idx; \
    for(idx = 0; ((0 != target) && (idx < size)); idx ++) \
    { \
        unsigned short data = chkBit[idx]; \
        if(target & data) \
        { \
            result |= resultBit[idx]; \
            target &= ~data; \
        } \
    } \
}

unsigned char copyBitByte(const unsigned short * chkBit, const unsigned char * resultBit, size_t size, unsigned short target)
{
    unsigned char result = 0;
    copyBit()
    return result;
}

unsigned short copyBitWord(const unsigned short * chkBit, const unsigned short * resultBit, size_t size, unsigned short target)
{
    unsigned short result = 0;
    copyBit()
    return result;
}

unsigned long copyBitDWord(const unsigned short * chkBit, const unsigned long * resultBit, size_t size, unsigned short target)
{
    unsigned long result = 0;
    copyBit()
    return result;
}

#define copyData() \
{ \
    size_t cnt, idx = 0; \
    if(dstCount <= srcCount) \
    { \
        for(cnt = 0; cnt < dstCount; cnt ++) \
        { \
            unsigned short target = dstIDs[cnt]; \
            idx = getIndexArray(&(srcIDs[0]), srcCount, target); \
            if(idx < srcCount) \
            { \
                dst[cnt].data = src[idx].data; \
                idx ++; \
                srcIDs = (&srcIDs[idx]); \
                src = &(src[idx]); \
                srcCount -= idx; \
            } \
            else \
            { \
                break; \
            } \
        } \
    } \
    else \
    { \
        for(cnt = 0; cnt < srcCount; cnt ++) \
        { \
            unsigned short target = srcIDs[cnt]; \
            idx = getIndexArray(&(dstIDs[0]), dstCount, target); \
            if(idx < dstCount) \
            { \
                dst[idx].data = src[cnt].data; \
                idx ++; \
                dstIDs = (&dstIDs[idx]); \
                dst = &(dst[idx]); \
                dstCount -= idx; \
            } \
            else \
            { \
                break; \
            } \
        } \
    } \
    return cnt; \
}

size_t copyDWord(union DWord dst[], const union DWord src[], const size_t dstIDs[], const size_t srcIDs[], size_t dstCount, size_t srcCount)
{
    copyData();
}

size_t copyWord(union Word dst[], const union Word src[], const size_t dstIDs[], const size_t srcIDs[], size_t dstCount, size_t srcCount)
{
    copyData();
}

size_t copyByte(union Byte dst[], const union Byte src[], const size_t dstIDs[], const size_t srcIDs[], size_t dstCount, size_t srcCount)
{
    copyData();
}

void SimpleAlloc_init(unsigned long buff[], size_t count)
{
    buff[0] = 1;
}

void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size)
{
    size_t size = (byte_size>>2) + ((byte_size&3) != 0);
    size_t idx  = (size_t)(buff[0]);
    size_t tail = idx + size;
    if(tail < count)
    {
        void * ptr = (void*)(&buff[idx]);
        buff[0] = tail;
        return ptr;
    }
    return NULL;
}

void RecCtrl_init(struct DataRecordCtrol * obj, union DWord * buff, const size_t * ids, const size_t * trs, const size_t * cnt)
{
    obj->buff = buff;
    obj->ids  = ids;
    obj->trs  = trs;
    obj->cnts = cnt;
    obj->dw_cnt = cnt[1] + cnt[2] + cnt[3];                             /* dword parameter count: uint32, int32, float  */
    obj->w_cnt  = cnt[4] + cnt[5];                                      /* word parameter count: uint16, int16          */
    obj->b_cnt  = cnt[6] + cnt[7];                                      /* byte parameter count: uint8, int8            */
    obj->cnt    = cnt[0];                                               /* parameter count                              */
    obj->size   = (obj->dw_cnt * 4) + (obj->w_cnt * 2) + obj->b_cnt;    /* byte size                                    */
}

unsigned char RecCtrl_dataSize(struct DataRecordCtrol * obj, unsigned short key)
{
    unsigned char size;
    size_t cnt = obj->dw_cnt;

    if((0 < cnt) && (key <= obj->ids[cnt - 1]))
    {
        size = 4;
    }
    else
    {
        cnt += obj->w_cnt;
        if((0 < obj->w_cnt) && (key <= obj->ids[cnt - 1]))
        {
            size = 2;
        }
        else
        {
            cnt += obj->b_cnt;
            if((0 < obj->b_cnt) && (key <= obj->ids[cnt - 1]))
            {
                size = 1;
            }
            else
            {
                size = 0;
            }
        }
    }
    return size;
}

void RecCtrl_copy(struct DataRecordCtrol * dst, const struct DataRecordCtrol * src)
{
    union Word * dst_ptr_w, * src_ptr_w;
    union Byte * dst_ptr_b, * src_ptr_b;
    size_t dst_w = dst->dw_cnt;
    size_t src_w = src->dw_cnt;
    size_t dst_b = dst->dw_cnt + dst->w_cnt;
    size_t src_b = src->dw_cnt + src->w_cnt;

    dst_ptr_w = &(dst->buff[dst_w].words[0]);
    src_ptr_w = &(src->buff[src_w].words[0]);
    dst_ptr_b = &(dst_ptr_w[dst->w_cnt].bytes[0]);
    src_ptr_b = &(src_ptr_w[src->w_cnt].bytes[0]);

    copyDWord(&(dst->buff[0]), &(src->buff[0]), &(dst->ids[0]),     &(src->ids[0]),     dst->dw_cnt, src->dw_cnt);
    copyWord( dst_ptr_w,       src_ptr_w,       &(dst->ids[dst_w]), &(src->ids[src_w]), dst->w_cnt,  src->w_cnt);
    copyByte( dst_ptr_b,       src_ptr_b,       &(dst->ids[dst_b]), &(src->ids[src_b]), dst->b_cnt,  src->b_cnt);
}

union DWord * RecCtrl_get(struct DataRecordCtrol * obj, size_t key)
{
    union DWord * ptr;

    size_t idx = getIndexArray(&(obj->ids[0]), obj->cnt, key);
    if(idx < obj->cnt)
    {
        if(idx < obj->dw_cnt)
        {
            ptr = (union DWord *)&(obj->buff[idx].data);
        }
        else if(idx < (obj->dw_cnt + obj->w_cnt))
        {
            size_t offset = obj->dw_cnt;
            ptr = &(obj->buff[offset]);
            ptr = (union DWord *)&(ptr->words[idx - offset]);
        }
        else
        {
            size_t offset = obj->dw_cnt;
            ptr = &(obj->buff[offset]);
            offset += obj->w_cnt;
            ptr = (union DWord *)&(ptr->words[obj->w_cnt].bytes[idx - offset]);
        }
    }
    else
    {
        ptr = NULL;
    }
    return ptr;
}

void RecStreamCtrl_init(struct RecStreamCtrl * stm, struct DataRecordCtrol * rec)
{
    stm->rec = rec;
    stm->fmt = rec->trs;
    stm->idx = 0;
    stm->cnt = 0;
    stm->pos = 0;
    stm->max = rec->size;
    stm->dsz  = RecCtrl_dataSize(rec, stm->fmt[0]);
    stm->pram = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
}

size_t RecStreamCtrl_Size(struct RecStreamCtrl * stm)
{
    return stm->max;
}

/**
 * input byte data to stream conrtol object(big endian)
 *
 * @param stm       byte stream control object
 * @param data      input data
 */
void RecStreamCtrl_in(struct RecStreamCtrl * stm, unsigned char data)
{
    if(stm->cnt < stm->max)
    {
        size_t        pos_max;
        union DWord * work;

        work = stm->pram;
        switch(stm->dsz)
        {
        case 1:
            work->byte.data = data;
            pos_max = 0;
            break;
        case 2:
            work->bytes[1-stm->pos].data = data;
            pos_max = 1;
            break;
        case 4:
            work->bytes[3-stm->pos].data = data;
            pos_max = 3;
            break;
        }
        if(stm->pos < pos_max)
        {
            stm->pos ++;
        }
        else
        {
            stm->pos = 0;
            stm->idx ++;
            stm->dsz  = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
            stm->pram = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
}

/**
 * get byte data from stream conrtol object(big endian)
 *
 * @param stm   byte stream control object
 * @return byte stream data
 */
unsigned char RecStreamCtrl_get(struct RecStreamCtrl * stm)
{
    unsigned char data = 0;

    if(stm->cnt < stm->max)
    {
        union DWord * work;
        size_t        pos_max;

        work = stm->pram;
        switch(stm->dsz)
        {
        case 1:
            data = work->byte.data;
            pos_max = 0;
            break;
        case 2:
            data = work->bytes[1-stm->pos].data;
            pos_max = 1;
            break;
        case 4:
            data = work->bytes[3-stm->pos].data;
            pos_max = 3;
            break;
        }
        if(stm->pos < pos_max)
        {
            stm->pos ++;
        }
        else
        {
            stm->pos = 0;
            stm->idx ++;
            stm->dsz  = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
            stm->pram = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
    return data;
}

/**
 * input byte data to stream conrtol object(little endian)
 *
 * @param stm       byte stream control object
 * @param data      input data
 */
void RecStreamCtrl_inl(struct RecStreamCtrl * stm, unsigned char data)
{
    if(stm->cnt < stm->max)
    {
        size_t        pos_max;
        union DWord * work;

        work = stm->pram;
        switch(stm->dsz)
        {
        case 1:
            work->byte.data = data;
            pos_max = 0;
            break;
        case 2:
            work->bytes[stm->pos].data = data;
            pos_max = 1;
            break;
        case 4:
            work->bytes[stm->pos].data = data;
            pos_max = 3;
            break;
        }
        if(stm->pos < pos_max)
        {
            stm->pos ++;
        }
        else
        {
            stm->pos = 0;
            stm->idx ++;
            stm->dsz  = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
            stm->pram = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
}

/**
 * get byte data from stream conrtol object(little endian)
 *
 * @param stm   byte stream control object
 * @return byte stream data
 */
unsigned char RecStreamCtrl_getl(struct RecStreamCtrl * stm)
{
    unsigned char data = 0;

    if(stm->cnt < stm->max)
    {
        union DWord * work;
        size_t        pos_max;

        work = stm->pram;
        switch(stm->dsz)
        {
        case 1:
            data = work->byte.data;
            pos_max = 0;
            break;
        case 2:
            data = work->bytes[stm->pos].data;
            pos_max = 1;
            break;
        case 4:
            data = work->bytes[stm->pos].data;
            pos_max = 3;
            break;
        }
        if(stm->pos < pos_max)
        {
            stm->pos ++;
        }
        else
        {
            stm->pos = 0;
            stm->idx ++;
            stm->dsz  = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
            stm->pram = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
    return data;
}

/**
 * caltrate data count on ring buffer
 *
 * @param top   top of ring buffer
 * @param tail  tail of ring buffer
 * @param max   max size of ring buffer
 * @return data count
 */
unsigned char calcOfRingBuffCount(unsigned char top, unsigned char tail, unsigned char max)
{
    unsigned char count;

    if(tail < top)
    {
        count = top - tail;
    }
    else if(tail > top)
    {
        count = top + (max - tail);
    }
    else
    {
        count = 0;
    }
    return count;
}

union Word swapByteOfWord(union Word src)
{
    union Word dst;

    dst.bytes[1].data = src.bytes[0].data;
    dst.bytes[0].data = src.bytes[1].data;
    return dst;
}

union Word calcCRC16_in(const unsigned short tbl[], union Word crc, unsigned char data)
{
    union Word temp;
    size_t idx;

    idx = crc.bytes[0].data ^ data;
    temp.data = tbl[idx];
    crc.bytes[0].data = temp.bytes[1].data ^ crc.bytes[1].data;
    crc.bytes[1].data = temp.bytes[0].data;
    return crc;
}

unsigned short calcCRC16(const unsigned short tbl[], const unsigned char * data, unsigned short size)
{
    union Word hex;
    unsigned short idx;

    hex.data = 0xffff;
    for(idx = 0; idx < size; idx ++)
    {
        hex = calcCRC16_in(tbl, hex, data[idx]);
    }
    return (swapByteOfWord(hex)).data;
}
