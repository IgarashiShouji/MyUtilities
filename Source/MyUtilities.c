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

size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned char target)
{
    getIndexArray(unsigned char);
    return count;
}

size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target)
{
    getIndexArray(unsigned short);
    return count;
}

size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned long target)
{
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
            idx = getIndexArrayWord(&(srcIDs[0]), srcCount, target); \
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
            idx = getIndexArrayWord(&(dstIDs[0]), dstCount, target); \
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

size_t copyDWord(union DWord dst[], const union DWord src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount)
{
    copyData();
}

size_t copyWord(union Word dst[], const union Word src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount)
{
    copyData();
}

size_t copyByte(union Byte dst[], const union Byte src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount)
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

void RecCtrl_init2(struct DataRecordCtrol * obj, union DWord * buff, const unsigned short * ids, const unsigned short cnt[][4], unsigned short recid, unsigned short rec_cnt)
{
    obj->buff = buff;
    obj->ids  = ids;
    obj->dwordCount  = cnt[recid][1];
    obj->wordCount   = cnt[recid][2];
    obj->byteCount   = cnt[recid][3];
    obj->dwordMaxIDs = cnt[rec_cnt][1];
    obj->wordMaxIDs  = cnt[rec_cnt][2];
    obj->byteMaxIDs  = cnt[rec_cnt][3];
}

void RecCtrl_init(struct DataRecordCtrol * obj, union DWord * buff, const unsigned short * ids, const unsigned short * cnt, size_t DwMax, size_t WdMax, size_t ByMax)
{
    obj->buff = buff;
    obj->ids  = ids;
    obj->dwordCount  = cnt[1];
    obj->wordCount   = cnt[2];
    obj->byteCount   = cnt[3];
    obj->dwordMaxIDs = DwMax;
    obj->wordMaxIDs  = WdMax;
    obj->byteMaxIDs  = ByMax;
}

unsigned char RecCtrl_dataSize(struct DataRecordCtrol * obj, unsigned short key)
{
    if(key < obj->dwordMaxIDs)
    {
        return 4;
    }
    if(key < obj->wordMaxIDs)
    {
        return 2;
    }
    if(key < obj->byteMaxIDs)
    {
        return 1;
    }
    return 0;
}

void RecCtrl_copy(struct DataRecordCtrol * dst, const struct DataRecordCtrol * src)
{
    size_t dst_begin_w = dst->dwordCount;
    size_t src_begin_w = src->dwordCount;
    size_t dst_begin_b = dst->dwordCount + dst->wordCount;
    size_t src_begin_b = src->dwordCount + src->wordCount;

    copyDWord(&(dst->buff[0]),                    &(src->buff[0]),                    &(dst->ids[0]),           &(src->ids[0]),           dst->dwordCount, src->dwordCount);
    copyWord( &(dst->buff[dst_begin_w].words[0]), &(src->buff[src_begin_w].words[0]), &(dst->ids[dst_begin_w]), &(src->ids[src_begin_w]), dst->wordCount,  src->wordCount);
    copyByte( &(dst->buff[dst_begin_b].bytes[0]), &(src->buff[src_begin_b].bytes[0]), &(dst->ids[dst_begin_b]), &(src->ids[src_begin_b]), dst->byteCount,  src->byteCount);
}

union DWord * RecCtrl_get(struct DataRecordCtrol * obj, unsigned short key)
{
    union DWord * ptr;

    if(key < obj->dwordMaxIDs)
    {
        size_t idx = getIndexArrayWord(&(obj->ids[0]), obj->dwordCount, key);
        ptr = (union DWord *)&(obj->buff[idx].data);
    }
    else if(key < obj->wordMaxIDs)
    {
        size_t begin = obj->dwordCount;
        size_t idx   = getIndexArrayWord(&(obj->ids[begin]), obj->wordCount, key);
        ptr = &(obj->buff[begin]);
        ptr = (union DWord *)&(ptr->words[idx]);
    }
    else if(key < obj->byteMaxIDs)
    {
        size_t begin = obj->dwordCount+obj->wordCount;
        size_t idx   = getIndexArrayWord(&(obj->ids[begin]), obj->byteCount, key);
        ptr = &(obj->buff[begin]);
        ptr = (union DWord *)&(ptr->bytes[idx]);
    }
    else
    {
        ptr = NULL;
    }
    return ptr;
}

void RecStreamCtrl_init(struct RecStreamCtrl * stm, struct DataRecordCtrol * rec, const unsigned short * fmt, size_t fmtCnt)
{
    size_t idx;

    stm->rec = rec;
    stm->fmt = fmt;
    stm->idx = 0;
    stm->cnt = 0;
    stm->max = 0;
    stm->pos = 0;
    for(idx=0; idx<fmtCnt; idx++)
    {
        stm->max += RecCtrl_dataSize(rec, fmt[idx]);
    }
    stm->dsz  = RecCtrl_dataSize(rec, fmt[0]);
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
