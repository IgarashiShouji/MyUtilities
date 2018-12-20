#include "Entity.hpp"
#include "DataRecord.h"

#include <iostream>
#include <cassert>

using namespace std;

enum
{
    DB_ID_001,
    DB_ID_002,
    DB_ID_003,
    DB_ID_004,
    DB_ID_005,
    DB_ID_006,
    DB_ID_007,
    DB_ID_MAX
};

static const unsigned char DataIDs[DB_ID_MAX] =
{
    DB_ID_001,
    DB_ID_002,
    DB_ID_003,
    DB_ID_004,
    DB_ID_005,
    DB_ID_006,
    DB_ID_007
};

static bool testStage1(void)
{
    cout << "test Stage 1: Continare class & utilities" << endl;
    static const unsigned char byte[7] = { 1, 2, 30, 40, 50, 61, 77 };
    size_t result=0;

    // ----------<< test of ConstArray template >>----------
    {
        MyEntity::ConstArray<unsigned char> array(byte, sizeof(byte));
        for(size_t idx=0, max=array.size(); idx<max; idx++)
        {
            assert(byte[idx] == array[idx]);
            result = idx+1;
        }
        assert(7==result);
    }

    // ----------<< test of getIndexArrayByte >>----------
    {
        result = getIndexArrayByte(byte, sizeof(byte), 1);
        assert(result == 0);
        result = getIndexArrayByte(byte, sizeof(byte), 2);
        assert(result == 1);
        result = getIndexArrayByte(byte, sizeof(byte), 30);
        assert(result == 2);
        result = getIndexArrayByte(byte, sizeof(byte), 40);
        assert(result == 3);
        result = getIndexArrayByte(byte, sizeof(byte), 50);
        assert(result == 4);
        result = getIndexArrayByte(byte, sizeof(byte), 61);
        assert(result == 5);
        result = getIndexArrayByte(byte, sizeof(byte), 77);
        assert(result == 6);
        result = getIndexArrayByte(byte, sizeof(byte), 35);
        assert(result == sizeof(byte));
    }

    // ----------<< test of getIndexArrayCString >>----------
    {
        static const char * testString[] =
        {
            "   Space Sring 2",                     // 0
            " Space Sring 1",                       // 1
            "Test 1",                               // 2
            "getIndexArrayCString ",                // 3
            "main",                                 // 4
            "return true",                          // 5
            "static const char * testString[] =",   // 6
        };
        result = getIndexArrayCString(testString, 7, "   Space Sring 2");
        assert(result == 0);
        result = getIndexArrayCString(testString, 7, " Space Sring 1");
        assert(result == 1);
        result = getIndexArrayCString(testString, 7, "Test 1");
        assert(result == 2);
        result = getIndexArrayCString(testString, 7, "getIndexArrayCString ");
        assert(result == 3);
        result = getIndexArrayCString(testString, 7, "main");
        assert(result == 4);
        result = getIndexArrayCString(testString, 7, "return true");
        assert(result == 5);
        result = getIndexArrayCString(testString, 7, "static const char * testString[] =");
        assert(result == 6);
        result = getIndexArrayCString(testString, 7, "Test");
        assert(result == 7);
        result = getIndexArrayCString(testString, 7, "");
        assert(result == 7);
    }

    // ----------<< test of ConstArrayMap >>----------
    {
        unsigned char byte[7] = { 1, 2, 30, 40, 50, 61, 77 };
        MyEntity::ConstArrayMap<unsigned char, unsigned char> src(byte, DataIDs, DB_ID_MAX);

        static const unsigned char keys1[2] = { DB_ID_002, DB_ID_004 };
        unsigned char result1[2] = { 0, 0 };
        MyEntity::ConstArrayMap<unsigned char, unsigned char> rec1(result1, keys1, 2);
        size_t cnt = rec1.copy(src);
        assert(cnt == 2);
        assert(result1[0]==2);
        assert(result1[1]==40);

        static const unsigned char keys2[3] = { DB_ID_002, DB_ID_003, DB_ID_004 };
        unsigned char result2[3] = { 0, 0, 0 };
        MyEntity::ConstArrayMap<unsigned char, unsigned char> rec2(result2, keys2, 3);
        rec2 = rec1;
        assert(result2[0]==2);
        assert(result2[1]==0);
        assert(result2[2]==40);
    }
    {
        unsigned short dst[2] = { 0, 0 };
        unsigned short src[3] = { 0x0005, 0x0030, 0x8877 };
        static const unsigned short dstIDs[] =
        {
            DB_ID_002,
            DB_ID_004,
        };
        static const unsigned short srcIDs[] =
        {
            DB_ID_002,
            DB_ID_003,
            DB_ID_004,
        };
        size_t result = copyWord((union Word *)dst, (const union Word *)src, dstIDs, srcIDs, (sizeof(dstIDs)/sizeof(dstIDs[0])), (sizeof(srcIDs)/sizeof(srcIDs[0])));
        assert(dst[0] == src[0]);
        assert(dst[1] == src[2]);
    }
    {
        static const unsigned short chk[] =
        {
            0x0001|0x0100,
            0x8000
        };
        static const unsigned long res[] =
        {
            0x80000000,
            0x00000001
        };
        assert(0x80000000 == copyBitDWord(chk, res, 2, 0x0001) );
        assert(0x80000000 == copyBitDWord(chk, res, 2, 0x0100) );
        assert(0x80000000 == copyBitDWord(chk, res, 2, 0x0101) );
        assert(0x80000000 == copyBitDWord(chk, res, 2, 0x01f1) );
        assert(0x00000001 == copyBitDWord(chk, res, 2, 0x8000) );
        assert(0x80000001 == copyBitDWord(chk, res, 2, 0x8001) );
        assert(0x80000001 == copyBitDWord(chk, res, 2, 0x8100) );
        assert(0x80000001 == copyBitDWord(chk, res, 2, 0x81f1) );
    }
    return true;
}

bool testStage2(void)
{
    cout << "test Stage 2: allocate class & utilities" << endl;

    unsigned long buffer[1024];
    SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
    void * ptr1 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 5);
    assert(ptr1 == &(buffer[1]));
    void * ptr2 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 18);
    assert(ptr2 == &(buffer[3]));
    return true;
}

/* 76543210 */
/* ||||||++- Data Size: 0:1Byte / 1:2Byte / 2:4Byte / 3:8Byte   */
/* |||||+--- Array Flag                                         */
/* |||++=--- Array n1                                           */
/* +++------ Array n2                                           */
/*           Array Size = 2^(n1) + 2^(n2)   min:2 / max:136     */
static const unsigned char DB_Type[DB_ID_MAX] =
{
    0x02,                   /* DB_ID_001: */
    0x02|0x04|0x20|0x08,    /* DB_ID_002: 4 = 2^1+2^1 */
    0x01,                   /* DB_ID_003: */
    0x00,                   /* DB_ID_004: */
    0x00|0x04|0xa0|0x00     /* DB_ID_005: 33 = 2^5+2^0 */
};

static const unsigned short DB_pos[DB_ID_MAX] =
{
    0,              /* DB_ID_001 */
    4,              /* DB_ID_002 */
    4+(4*4),        /* DB_ID_003 */
    4+(4*4)+2,      /* DB_ID_004 */
    4+(4*4)+2+1     /* DB_ID_005 */
};

struct DataCount
{
    unsigned short Count;
    unsigned short dwCount;
    unsigned short wCount;
    unsigned short bCount;
};

union DWord * getData(const unsigned short pos[], unsigned char * data, unsigned short id)
{
    size_t idx = pos[id];
    union DWord * ptr = (union DWord *)&data[idx];
    return ptr;
}

bool testStage3()
{
    cout << "test Stage 3: Data Base & recoard Class & utilities" << endl;

    unsigned char data[64];
    union DWord * ptr = getData(DB_pos, data, DB_ID_002);
    assert(&data[4]==&(ptr->byte[0].data));

    // 4 byte data: DB_ID_001, DB_ID_002, DB_ID_003
    // 2 byte data: DB_ID_004
    // 1 byte data: DB_ID_005, DB_ID_006
    const unsigned short dbCnt[4]   = { 6, 3, 1, 2 };
    const unsigned short dbIDs[6]   = { DB_ID_001, DB_ID_002, DB_ID_003, DB_ID_004, DB_ID_005, DB_ID_006 };
    union DWord          dbBuff[3+1+1];
    const unsigned short rec1Cnt[4] = { 4, 2, 1, 1 };
    const unsigned short rec1IDs[4] = { DB_ID_001, DB_ID_003, DB_ID_004, DB_ID_006 };
    union DWord          rec1Buff[2+1+1];
    const unsigned short rec2Cnt[4] = { 2, 0, 1, 1 };
    const unsigned short rec2IDs[2] = { DB_ID_004, DB_ID_006 };
    union DWord          rec2Buff[0+1+1];

    MyEntity::DataRecord db(dbBuff, dbIDs, dbCnt);
    MyEntity::DataRecord rec1(rec1Buff, rec1IDs, rec1Cnt);
    MyEntity::DataRecord rec2(rec2Buff, rec2IDs, rec2Cnt);
    rec2 = db;
    rec1 = rec2;
    unsigned short rec1_fmt[4] = { DB_ID_003, DB_ID_006, DB_ID_001, DB_ID_004 };
    {
        MyEntity::DataRecordStream stm(rec1, rec1_fmt);
        const unsigned char data[8+2+1] = { 0, 1, 2, 3, 4, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xbb };
        for(auto item : data)
        {
            stm << item;
        }
        for(auto key: rec1_fmt)
        {
            switch(rec1.dataSize(key))
            {
            case 1:
                printf("  - rec1[%d]: %02x\n", 1+key, rec1[key].byte[0].data);
                break;
            case 2:
                printf("  - rec1[%d]: %04x\n", 1+key, rec1[key].word[0].data);
                break;
            case 4:
                printf("  - rec1[%d]: %08x\n", 1+key, static_cast<unsigned int>(rec1[key].data));
                break;
            }
        }
        assert(rec1[DB_ID_003].data         == 0x00010203);
        assert(rec1[DB_ID_006].byte[0].data == 0x04);
        assert(rec1[DB_ID_001].data         == 0x55555555);
        assert(rec1[DB_ID_004].word[0].data == 0xaabb);
        unsigned char result[sizeof(data)] = { 0 };
        stm.clear();
        for(size_t cnt = 0; stm.count() < stm.size(); cnt ++)
        {
            result[cnt] = stm.get();
        }
        assert(0 == memcmp(data, result, sizeof(data)));
        {
            union DWord buff[2+1+1];
            MyEntity::DataRecord tmpRec(buff, rec1);
            tmpRec = rec1;
            MyEntity::DataRecordStream stm(tmpRec, rec1_fmt);
            unsigned char result[sizeof(data)] = { 0 };
            for(size_t cnt = 0; stm.count() < stm.size(); cnt ++)
            {
                result[cnt] = stm.get();
            }
            assert(0 == memcmp(data, result, sizeof(data)));
        }
    }
    db = rec1;
    assert(0x00010203 == dbBuff[2].data);
    rec2 = db;
    assert(rec2[DB_ID_004].word[0].data == 0xaabb);
    assert(rec2[DB_ID_006].byte[0].data == 0x04);
    {
        union DWord buff1[RSZ_Rec001];
        union DWord buff2[RSZ_Rec002];
        MyEntity::DataRecord rec1(buff1, tblRecIDs[REC_Rec001], tblRecSize[REC_Rec001]);
        MyEntity::DataRecord rec2(buff2, tblRecIDs[REC_Rec002], tblRecSize[REC_Rec002]);
        rec2 = rec1;
    }
    return true;
}

int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    assert(testStage1());
    assert(testStage2());
    assert(testStage3());
    cout << "pass." << endl;
    cout << endl;
    return 0;
}
