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


unsigned short CalcCRC16::calc(const unsigned char * data, unsigned int size, const unsigned short * crc_tbl)
{
    CalcCRC16 crc(crc_tbl);
    for(unsigned int idx = 0; idx < size; idx ++)
    {
        crc << data[idx];
    }
    return (*crc);
}
