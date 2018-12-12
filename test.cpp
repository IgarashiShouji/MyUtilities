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


void SimpleAlloc_init(unsigned long buff[], size_t count)
{
    buff[0] = 1;
}

void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size)
{
    size_t size = (byte_size>>2) + ((byte_size&3) != 0);
    size_t idx = buff[0];
    size_t tail = idx + size;
    if(tail < count)
    {
        void * ptr = (void*)(&buff[idx]);
        buff[0] = tail;
        return ptr;
    }
    return NULL;
}

bool test(void)
{
    unsigned long buffer[1024];
    SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
    void * ptr1 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 5);
    assert(ptr1 == &(buffer[1]));
    void * ptr2 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 18);
    assert(ptr2 == &(buffer[3]));
    return true;
}

int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    cout << "  Code Test Stage 1." << endl;
    assert(testStage1());
    assert(test());
    cout << endl;
    cout << "pass." << endl;
    cout << endl;
    return 0;
}
