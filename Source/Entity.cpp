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
DataRecordStream & DataRecordStream::operator << (const unsigned char data)
{
    static void (* const func[2])(struct RecStreamCtrl * stm, unsigned char data) = {RecStreamCtrl_in, RecStreamCtrl_inl};
    (func[litle])(&stm, data);
    return *this;
}
unsigned char DataRecordStream::get(void)
{
    static unsigned char (* const func[2])(struct RecStreamCtrl * stm) = {RecStreamCtrl_get, RecStreamCtrl_getl};
    unsigned char result = (func[litle])(&stm);
    return result;
}
