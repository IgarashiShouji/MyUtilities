/**
 * Entity Class File
 *
 * @file    Entity.cpp
 * @brief   C++ Entity Utilitis
 * @author  Shouji, Igarashi
 *
 * (c) 2018 Shouji, Igarashi.
 */

#include "Entity.hpp"
#include <errno.h>

using namespace MyEntity;

signed int ConstCString::compere(const char * & str) const
{
    return strcmp(this->str, str);
}

unsigned short CalcCRC16::calc(const unsigned char * data, unsigned int size, const unsigned short * crc_tbl)
{
    CalcCRC16 crc(crc_tbl);
    for(unsigned int idx = 0; idx < size; idx ++)
    {
        crc << data[idx];
    }
    return (*crc);
}

/**
 * Get data item size
 *
 * @param key       data id key
 * @return data item size
 */
unsigned char DataRecord::dataSize(unsigned short key) const
{
    if(dword.getIndex(key) < dword.size())
    {
        return 4;
    }
    if(word.getIndex(key) < word.size())
    {
        return 2;
    }
    if(byte.getIndex(key) < byte.size())
    {
        return 1;
    }
    return 0;
}

/**
 * Copy data record
 *
 * @param src       copy source of data record object
 * @return this object
 */
DataRecord & DataRecord::operator = (DataRecord & src)
{
    dword = src.getDWordList();
    word  = src.getWordList();
    byte  = src.getByteList();
    return *this;
}

/**
 * reference of data item.
 *
 * @param key       data id key
 * @return data item
 */
union DWord & DataRecord::operator [](unsigned short key)
{
    union DWord * ptr = nullptr;
    switch(dataSize(key))
    {
    case 1:
        ptr = reinterpret_cast<union DWord *>(&byte[key]);
        return *ptr;
    case 2:
        ptr = reinterpret_cast<union DWord *>(&word[key]);
        return *ptr;
    case 4:
        return dword[key];
    default:
        break;
    }
    throw EINVAL;
    static union DWord result;
    return result;
}


/**
 * date stream input
 *
 * @param data      input data
 * @return this object
 */
DataRecordStream & DataRecordStream::operator << (unsigned char data)
{
    if(cnt < max)
    {
        size_t pos_max = 0;
        switch(dsz)
        {
        case 1:
            {
                auto & dst = rec.getByteList();
                dst[fmt[idx]].data = data;
            }
            break;
        case 2:
            {
                auto & dst = rec.getWordList();
                dst[fmt[idx]].byte[1-pos].data = data;
            }
            pos_max = 1;
            break;
        case 4:
            {
                auto & dst = rec.getDWordList();
                dst[fmt[idx]].byte[3-pos].data = data;
            }
            pos_max = 3;
            break;
        }
        if(pos < pos_max)
        {
            pos ++;
        }
        else
        {
            pos = 0;
            idx ++;
            dsz = rec.dataSize(fmt[idx]);
        }
        cnt ++;
    }
    return *this;
}
