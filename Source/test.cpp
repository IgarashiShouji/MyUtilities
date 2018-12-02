#include "Entity.hpp"

#include <iostream>
#include <cassert>

using namespace std;

static bool testStage1(void)
{
    static const unsigned char byte[7] = { 1, 2, 3, 4, 5, 6, 7 };
    MyEntity::ConstArray<unsigned char> array(byte, sizeof(byte));
    size_t result=0, count = 7;
    for(size_t idx=0, max=array.size(); idx<max; idx++)
    {
        assert(byte[idx] == array[idx]);
        result = idx+1;
    }
    assert(count==result);
    return true;
}


int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    cout << "  Code Test Stage 1." << endl;
    assert(testStage1());

    cout << endl;
    cout << "Test End." << endl;
    cout << endl;
    return 0;
}
