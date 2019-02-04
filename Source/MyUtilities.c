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
        size_t mid = top + (len>>1); \
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

struct Range getRangeOfStringList(const char * const list[], size_t count, size_t sidx, char target)
{
    struct Range result;
    result.idx = 0;
    result.cnt = count;
    if(0 < count)
    {
        if((list[0])[sidx] != target)
        {
            size_t idx, len;
            for(idx=0, len=count; 0 != len;)
            {
                size_t mid = idx + (len>>1);
                char data = (list[mid])[sidx];
                if(data == target)
                {
                    result.idx = mid;
                }
                else
                {
                    if(0 != idx)
                    {
                        break;
                    }
                }
                if(data < target)
                {
                    idx = mid;
                }
                if(1 & len)
                {
                    if(1 < len)
                    {
                        len = (len+1)>>1;
                        continue;
                    }
                }
                len >>= 1;
            }
        }
        if((list[count-1])[sidx] != target)
        {
            size_t idx, len, max = 0;
            for(idx = 0, len = count; 0 != len;)
            {
                size_t mid = idx + (len>>1);
                char data = (list[mid])[sidx];
                if(data <= target)
                {
                    idx = mid;
                    max = idx;
                }
                if(1 & len)
                {
                    if(1 < len)
                    {
                        len = (len+1)>>1;
                        continue;
                    }
                }
                len >>= 1;
            }
            result.cnt = 1 + (max - result.idx);
        }
        else
        {
            result.cnt = count - result.idx;
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
    size_t idx1, idx2; \
    size_t max1 = dstCount; \
    size_t max2 = srcCount; \
 \
    for(idx1 = 0, idx2 = 0; (idx1 < max1) && (0 < max2); idx1 ++) \
    { \
        idx2 = getIndexArrayWord(&(srcIDs[idx2]), max2, dstIDs[idx1]); \
        if(idx2 < max2) \
        { \
            dst[idx1].data = src[idx2].data; \
            max2 -= idx2; \
        } \
    } \
    return 0; \
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

void RecCtrl_copy(struct DataRecordCtrol * dst, struct DataRecordCtrol * src)
{
    copyDWord(
      &(dst->buff[0]), &(src->buff[0]),
      &(dst->ids[0]),  &(src->ids[0]),
      dst->dwordCount, src->dwordCount);
    copyWord(
      &(dst->buff[dst->dwordCount].word[0]), &(src->buff[src->dwordCount].word[0]),
      &(dst->ids[ dst->dwordCount]),         &(src->ids[ src->dwordCount]),
      dst->wordCount,                        src->wordCount);
    copyByte(
      &(dst->buff[dst->dwordCount+dst->wordCount].byte[0]), &(src->buff[src->dwordCount+src->wordCount].byte[0]),
      &(dst->ids[ dst->dwordCount+dst->wordCount]),         &(src->ids[ src->dwordCount+src->wordCount]),
      dst->byteCount,                                       src->byteCount);
}

union DWord * RecCtrl_get(struct DataRecordCtrol * obj, unsigned short key)
{
    size_t idx;
    union DWord * ptr;
    switch(RecCtrl_dataSize(obj, key))
    {
    case 1:
        idx = getIndexArrayWord(&(obj->ids[obj->dwordCount+obj->wordCount]), obj->byteCount, key);
        ptr = &(obj->buff[obj->dwordCount+obj->wordCount]);
        ptr = (union DWord *)&(ptr->byte[idx].data);
        break;
    case 2:
        idx = getIndexArrayWord(&(obj->ids[obj->dwordCount]), obj->wordCount, key);
        ptr = &(obj->buff[obj->dwordCount]);
        ptr = (union DWord *)&(ptr->word[idx].data);
        break;
    case 4:
        idx = getIndexArrayWord(&(obj->ids[0]), obj->dwordCount, key);
        ptr = (union DWord *)&(obj->buff[idx].data);
        break;
    default:
        ptr = NULL;
        break;
    }
    return ptr;
}

void RecStreamCtrl_init(struct RecStreamCtrl * stm, struct DataRecordCtrol * rec, const unsigned short * fmt, size_t fmtCnt)
{
    size_t idx;

    stm->fmt = fmt;
    stm->idx = 0;
    stm->cnt = 0;
    stm->max = 0;
    stm->pos = 0;
    for(idx=0; idx<fmtCnt; idx++)
    {
        stm->max += RecCtrl_dataSize(rec, fmt[idx]);
    }
    stm->dsz = RecCtrl_dataSize(rec, fmt[0]);
}

size_t RecStreamCtrl_Size(struct RecStreamCtrl * stm)
{
    return stm->max;
}

void RecStreamCtrl_in(struct RecStreamCtrl * stm, unsigned char data)
{
    if(stm->cnt < stm->max)
    {
        size_t pos_max = 0;
        union DWord * work = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        switch(stm->dsz)
        {
        case 1:
            work->byte[0].data = data;
            break;
        case 2:
            work->byte[1-stm->pos].data = data;
            pos_max = 1;
            break;
        case 4:
            work->byte[3-stm->pos].data = data;
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
            stm->dsz = stm->dsz = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
}

unsigned char RecStreamCtrl_get(struct RecStreamCtrl * stm)
{
    unsigned char data = 0;;
    if(stm->cnt < stm->max)
    {
        size_t pos_max = 0;
        union DWord * work = RecCtrl_get(stm->rec, stm->fmt[stm->idx]);
        switch(stm->dsz)
        {
        case 1:
            data = work->byte[0].data;
            break;
        case 2:
            data = work->byte[1-stm->pos].data;
            pos_max = 1;
            break;
        case 4:
            data = work->byte[3-stm->pos].data;
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
            stm->dsz = stm->dsz = RecCtrl_dataSize(stm->rec, stm->fmt[stm->idx]);
        }
        stm->cnt ++;
    }
    return data;
}
