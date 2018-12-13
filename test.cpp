#include "Entity.hpp"

#include <iostream>
#include <cassert>

using namespace std;

static bool testStage1(void)
{
    static const unsigned char byte[7] = { 1, 2, 30, 40, 50, 61, 77 };
    MyEntity::ConstArray<unsigned char> array(byte, sizeof(byte));
    size_t result=0, count = 7;
    for(size_t idx=0, max=array.size(); idx<max; idx++)
    {
        assert(byte[idx] == array[idx]);
        result = idx+1;
    }
    assert(count==result);

    /* test getIndexArrayByte */
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

    /* test getIndexArrayCString */
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
    return true;
}

bool testStage2(void)
{
    unsigned long buffer[1024];
    SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
    void * ptr1 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 5);
    assert(ptr1 == &(buffer[1]));
    void * ptr2 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 18);
    assert(ptr2 == &(buffer[3]));
    return true;
}

enum
{
    DB_ID_001,
    DB_ID_002,
    DB_ID_003,
    DB_ID_004,
    DB_ID_005,
    DB_ID_MAX
};

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

union DWord * getData(const unsigned short pos[], unsigned char * data, unsigned short id)
{
    size_t idx = pos[id];
    union DWord * ptr = (union DWord *)&data[idx];
    return ptr;
}

bool testStage3()
{
    unsigned char data[64];
    union DWord * ptr = getData(DB_pos, data, DB_ID_002);
    assert(&data[4]==&(ptr->byte[0]));
    unsigned short dst[2] = { 0, 0 };
    unsigned short src[3] = { 0x0005, 0x0030, 0x8877 };
    size_t result = copyWord((union Word *)dst, (const union Word *)src, dstIDs, srcIDs, (sizeof(dstIDs)/sizeof(dstIDs[0])), (sizeof(srcIDs)/sizeof(srcIDs[0])));
    assert(dst[0] == src[0]);
    assert(dst[1] == src[2]);
    return true;
}

int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    cout << "  Code Test Stage 1." << endl;
    assert(testStage1());
    assert(testStage2());
    assert(testStage3());
    cout << endl;
    cout << "pass." << endl;
    cout << endl;
    return 0;
}
