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
    return true;
}


int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    cout << "  Code Test Stage 1." << endl;
    assert(testStage1());
    cout << endl;
    cout << "pass." << endl;
    cout << endl;
    return 0;
}
