#include "Entity.hpp"
#include "DataRecord.h"

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

static bool testStage1(void)
{
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
        static const unsigned short dstIDs[] = { DB_ID_002,            DB_ID_004, };
        static const unsigned short srcIDs[] = { DB_ID_002, DB_ID_003, DB_ID_004, };
        size_t result = copyWord((union Word *)dst, (const union Word *)src, dstIDs, srcIDs, (sizeof(dstIDs)/sizeof(dstIDs[0])), (sizeof(srcIDs)/sizeof(srcIDs[0])));
        assert(dst[0] == src[0]);
        assert(dst[1] == src[2]);
    }
    {
        unsigned short dst[3] = { 0, 0, 0 };
        unsigned short src[2] = { 0x0005, 0x8877 };
        static const unsigned short dstIDs[] = { DB_ID_002, DB_ID_004, DB_ID_006, };
        static const unsigned short srcIDs[] = { DB_ID_002,            DB_ID_006, };
        size_t result = copyWord((union Word *)dst, (const union Word *)src, dstIDs, srcIDs, (sizeof(dstIDs)/sizeof(dstIDs[0])), (sizeof(srcIDs)/sizeof(srcIDs[0])));
        assert(dst[0] == src[0]);
        assert(dst[1] == 0);
        assert(dst[2] == src[1]);
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

class Object
{
private:
    static unsigned long buffer[1024];
    unsigned short dummy[2];
public:
    Object(void) { }
    virtual ~Object(void) { }
    static void clean(void);
    static unsigned long * ref(void);
    static void * operator new(size_t size);
    static void operator delete(void * ptr, size_t size);
};
unsigned long Object::buffer[1024] = {0};
void Object::clean(void)
{
    SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
}
unsigned long * Object::ref(void)
{
    return &(buffer[0]);
}
void * Object::operator new(size_t size)
{
    static bool init = false;
    if( !init )
    {
        init = true;
        SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
    }
    printf("  new size = %d\n", static_cast<int>(size));
    void * ptr = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), size);
    return ptr;
}
void Object::operator delete(void * ptr, size_t size)
{
}
bool testStage2(void)
{
    cout << "test Stage 2: allocate class & utilities" << endl;
    union
    {
        Object * obj;
        unsigned int addr;
    } data1;
    union
    {
        unsigned long * obj;
        unsigned int addr;
    } data2;

    unsigned long buffer[1024];
    SimpleAlloc_init(buffer, (sizeof(buffer)/sizeof(buffer[0])));
    void * ptr1 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 5);
    assert(ptr1 == &(buffer[1]));
    void * ptr2 = SimpleAlloc_new(buffer, (sizeof(buffer)/sizeof(buffer[0])), 18);
    assert(ptr2 == &(buffer[3]));
    {
        Object * obj1 = new Object();
        Object * obj2 = new Object();
        assert(&((Object::ref())[1]) == reinterpret_cast<unsigned long *>(obj1));
        assert(&((Object::ref())[5]) == reinterpret_cast<unsigned long *>(obj2));
        data1.obj = obj1;
        data2.obj = &((Object::ref())[1]);
        printf("  obj1 = %08x, %08x\n", data1.addr, data2.addr);
        data1.obj = obj2;
        data2.obj = &((Object::ref())[5]);
        printf("  obj2 = %08x, %08x\n", data1.addr, data2.addr);
    }
    Object::clean();
    {
        Object * obj1 = new Object();
        Object * obj2 = new Object();
        assert(&((Object::ref())[1]) == reinterpret_cast<unsigned long *>(obj1));
        assert(&((Object::ref())[5]) == reinterpret_cast<unsigned long *>(obj2));
        data1.obj = obj1;
        data2.obj = &((Object::ref())[1]);
        printf("  obj1 = %08x, %08x\n", data1.addr, data2.addr);
        data1.obj = obj2;
        data2.obj = &((Object::ref())[5]);
        printf("  obj2 = %08x, %08x\n", data1.addr, data2.addr);
    }

    unsigned long buff[64];
    {
         MyEntity::SimpleAllocator<int> heap(buff, (sizeof(buff)/sizeof(buff[0])));
         heap.init();
         printf("  heap.size(%d)\n", static_cast<int>(heap.size()));
         vector<int, MyEntity::SimpleAllocator<int>> arry(5, heap);
         for(size_t idx = 0; idx <  arry.size(); idx ++)
         {
             arry[idx] = idx * 10;
         }
         for(size_t idx = 0; idx <  arry.size(); idx ++)
         {
             printf("  arry[%d] = %d\n", static_cast<int>(idx), reinterpret_cast<int>(arry[idx]));
         }
         arry.clear();
         printf("  arry.size(%d)\n", static_cast<int>(arry.size()));
         printf("  heap.size(%d)\n", static_cast<int>(heap.size()));
    }
    {
         MyEntity::SimpleAllocator<int> heap(buff, (sizeof(buff)/sizeof(buff[0])));
         printf("  heap.size(%d)\n", static_cast<int>(heap.size()));
         vector<int, MyEntity::SimpleAllocator<int>> arry(5, heap);
         for(size_t idx = 0; idx <  arry.size(); idx ++)
         {
             arry[idx] = idx * 12;
         }
         for(size_t idx = 0; idx <  arry.size(); idx ++)
         {
             printf("  arry[%d] = %d\n", static_cast<int>(idx), reinterpret_cast<int>(arry[idx]));
         }
         arry.clear();
         printf("  arry.size(%d)\n", static_cast<int>(arry.size()));
         printf("  heap.size(%d)\n", static_cast<int>(heap.size()));
         heap.init();
         printf("  heap.size(%d)\n", static_cast<int>(heap.size()));
    }
    return true;
}

bool testStage3()
{
    cout << "test Stage 3: Data Base & recoard Class & utilities" << endl;

    // C++ Interface Test
    {
        union DWord          dbBuff[RCNT_Rec001];
        union DWord          rec2Buff[RCNT_Rec002];
        union DWord          rec4Buff[RCNT_Rec004];
        union DWord          rec12Buff[RCNT_Rec012];

        MyEntity::DataRecord RecTable(db, Rec001, dbBuff);
        MyEntity::DataRec rec2(rec2Buff, Rec002);
        MyEntity::DataRec rec4(rec4Buff, Rec004);
        MyEntity::DataRec rec12(rec12Buff, Rec012);

        MyEntity::DataRecordStream stm(*rec12, trs_Rec012, (sizeof(trs_Rec012)/sizeof(trs_Rec012[0])));
        static const unsigned char data[4+4+1+1] = {0x7f, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x00, 0x00, 0x55, 0xaa };
        printf("  Data In: ");
        /* Recive Check(to Record) */
        for(auto item : data)
        {
            printf( "%02x", item);
            stm << item;
        }
        printf("\n");
        printf("  rec12[Value01].data = 0x%08x\n", static_cast<unsigned int>(rec12[Value01].data));
        printf("  rec12[Value02].data = 0x%08x\n", static_cast<unsigned int>(rec12[Value02].data));
        printf("  rec12[Value01Unit].byte[0].data = 0x%02x\n", rec12[Value01Unit].byte.data);
        printf("  rec12[Value02Unit].byte[0].data = 0x%02x\n", rec12[Value02Unit].byte.data);
        assert(rec12[Value01].data             == 0x7fffffff);
        assert(rec12[Value01Unit].byte.data    == 0x55);
        assert(rec12[Value02].data             == 0x7fff0000);
        assert(rec12[Value02Unit].byte.data    == 0xaa);
        db = *rec12;
        rec2 = db;
        rec4 = db;
        assert(rec2[Value01].data             == 0x7fffffff);
        assert(rec2[Value01Unit].byte.data    == 0x55);
        assert(rec4[Value02].data             == 0x7fff0000);
        assert(rec4[Value02Unit].byte.data    == 0xaa);

        /* Send Data Check(to byte binary) */
        stm.clear();
        unsigned char result[sizeof(data)] = {0};
        for(size_t cnt = 0; stm.count() < stm.size(); cnt ++)
        {
            result[cnt] = stm.get();
        }
        assert(0 == memcmp(data, result, sizeof(data)));
        /* Send Data Check(to byte binary) */
        MyEntity::DataRecordStream toBin(*rec12, trs_Rec012, (sizeof(trs_Rec012)/sizeof(trs_Rec012[0])));
        unsigned char result2[sizeof(data)] = {0};
        size_t cnt = 0;
        for(; toBin.count() < toBin.size(); cnt ++)
        {
            result2[cnt] = toBin.get();
        }
        assert(10 == cnt);
        assert(0 == memcmp(data, result2, cnt));
    }

    // C Interface Test
    {
        union DWord          dbBuff[RCNT_Rec001];
        union DWord          rec2Buff[RCNT_Rec002];
        union DWord          rec4Buff[RCNT_Rec004];
        union DWord          rec12Buff[RCNT_Rec012];

        struct DataRecordCtrol dbCtrl;
        struct DataRecordCtrol rec2;
        struct DataRecordCtrol rec4;
        struct DataRecordCtrol rec12;
        union DWord * val;

        memset(&(dbBuff[0]), 0, sizeof(dbBuff));
        memset(&(rec2Buff[0]), 0, sizeof(rec2Buff));
        memset(&(rec4Buff[0]), 0, sizeof(rec4Buff));
        memset(&(rec12Buff[0]), 0, sizeof(rec12Buff));
        RecCtrl_init(&dbCtrl, dbBuff,    tblRecIDs[Rec001], tblRecSize[Rec001], ID_DWORD_MAX, ID_WORD_MAX, ID_BYTE_MAX);
        RecCtrl_init(&rec2,   rec2Buff,  tblRecIDs[Rec002], tblRecSize[Rec002], ID_DWORD_MAX, ID_WORD_MAX, ID_BYTE_MAX);
        RecCtrl_init(&rec4,   rec4Buff,  tblRecIDs[Rec004], tblRecSize[Rec004], ID_DWORD_MAX, ID_WORD_MAX, ID_BYTE_MAX);
        RecCtrl_init(&rec12,  rec12Buff, tblRecIDs[Rec012], tblRecSize[Rec012], ID_DWORD_MAX, ID_WORD_MAX, ID_BYTE_MAX);
        {
            static const unsigned char data[4+4+1+1] = {0x7f, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x00, 0x00, 0x55, 0xaa };
            struct RecStreamCtrl stm;
            size_t idx;

            RecStreamCtrl_init(&stm, &rec12, trs_Rec012, (sizeof(trs_Rec012)/sizeof(trs_Rec012[0])));
            for(idx=0; idx<sizeof(data); idx++)
            {
                RecStreamCtrl_in(&stm, data[idx]);
            }

            RecCtrl_copy(&dbCtrl, &rec12);
            RecCtrl_copy(&rec2, &dbCtrl);
            RecCtrl_copy(&rec4, &dbCtrl);

            val = RecCtrl_get(&rec2, Value01);     assert(val->data         == 0x7fffffff);
            val = RecCtrl_get(&rec2, Value01Unit); assert(val->byte.data    == 0x55);
            val = RecCtrl_get(&rec4, Value02);     assert(val->data         == 0x7fff0000);
            val = RecCtrl_get(&rec4, Value02Unit); assert(val->byte.data    == 0xaa);
        }
        {
            static const unsigned char data[4+4+1+1] = {0x7f, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x00, 0x00, 0x55, 0xaa };
            unsigned char result[sizeof(data)] = {0};
            struct RecStreamCtrl stm;
            size_t idx;

            RecStreamCtrl_init(&stm, &rec12, trs_Rec012, (sizeof(trs_Rec012)/sizeof(trs_Rec012[0])));
            for(idx=0; idx<RecStreamCtrl_Size(&stm); idx++)
            {
                result[idx] = RecStreamCtrl_get(&stm);
            }
            assert(0 == memcmp(&(result[0]), &(data[0]), RecStreamCtrl_Size(&stm)));
        }
    }
    return true;
}

bool testStage4(void)
{
    cout << "test Stage 4: incremental search for C style string." << endl;
    /* sorted string list */
    static const unsigned char cmd01[] = "add";
    static const unsigned char cmd02[] = "bc";
    static const unsigned char cmd03[] = "dump.eeprom";
    static const unsigned char cmd04[] = "dump.flash";
    static const unsigned char cmd05[] = "dump.ram";
    static const unsigned char cmd06[] = "dump.rom";
    static const unsigned char cmd07[] = "echo";
    static const unsigned char cmd08[] = "edit.ram";
    static const unsigned char cmd09[] = "eval";
    static const unsigned char cmd10[] = "format";
    static const unsigned char cmd11[] = "format.eeprom";
    static const unsigned char cmd12[] = "format.flash";
    static const unsigned char cmd13[] = "help";
    static const unsigned char cmd14[] = "xmodem";
    static const unsigned char cmd15[] = "zmodem";
    static const unsigned char * const cmdList[] = { cmd01, cmd02, cmd03, cmd04, cmd05, cmd06, cmd07, cmd08, cmd09, cmd10, cmd11, cmd12, cmd13, cmd14, cmd15 };
    static const unsigned char cmdList_sz[] = { sizeof(cmd01), sizeof(cmd02), sizeof(cmd03), sizeof(cmd04), sizeof(cmd05), sizeof(cmd06), sizeof(cmd07), sizeof(cmd08), sizeof(cmd09), sizeof(cmd10), sizeof(cmd11), sizeof(cmd12), sizeof(cmd13), sizeof(cmd14), sizeof(cmd15) };
    {
        const unsigned char cmd[] = "dump.ram 0x8000,64";
        printf("  test 1: \n");
        size_t tidx=0;
        struct Range res = { 0, (sizeof(cmdList)/sizeof(cmdList[0])) };
        unsigned char delim = ' ';
        for(size_t idx = 0, max = sizeof(cmd); (idx < max); idx++)
        {
            struct Range tmp;
            if(delim == cmd[idx])
            {
                if(cmdList[res.idx][idx] != '\0')
                {   // no match
                    res.idx = 0;
                    res.cnt = 0;
                }
                break;
            }
            //tmp = getRangeOfStringList(&(cmdList[res.idx]), res.cnt, idx, cmd[idx]);
            tmp = getRangeOfListByte(&(cmdList[res.idx]), &(cmdList_sz[res.idx]), res.cnt, idx, cmd[idx]);
            res.idx += tmp.idx;
            res.cnt  = tmp.cnt;
            printf("    check : %d, %d: %c: %s\n", static_cast<int>(res.idx), static_cast<int>(res.cnt), cmd[idx], cmd);
            for(size_t idx=0, max=res.cnt; idx<max; idx++)
            {
                printf("      %d: %s\n", static_cast<int>(idx), cmdList[res.idx + idx]);
            }
        }
        printf("    result: %d, %d: %s\n", static_cast<int>(res.idx), static_cast<int>(res.cnt), cmdList[res.idx]);
        assert(res.idx == 4);
        assert(res.cnt == 1);
    }
    {
        const char * cmd = "dump-ram2 0x8000,64";
        printf("  test 2: ");
        size_t tidx=0;
        struct Range res = { 0, (sizeof(cmdList)/sizeof(cmdList[0])) };
        char delim = ' ';
        for(size_t idx = 0, max = strlen(cmd); (idx < max); idx++)
        {
            struct Range tmp;
            if(delim == cmd[idx])
            {
                if(cmdList[res.idx][idx] != '\0')
                {   // no match
                    res.idx = 0;
                    res.cnt = 0;
                }
                break;
            }
            //tmp = getRangeOfStringList(&(cmdList[res.idx]), res.cnt, idx, cmd[idx]);
            tmp = getRangeOfListByte(&(cmdList[res.idx]), &(cmdList_sz[res.idx]), res.cnt, idx, cmd[idx]);
            res.idx += tmp.idx;
            res.cnt  = tmp.cnt;
        }
        printf("%d, %d: %s\n", static_cast<int>(res.idx), static_cast<int>(res.cnt), cmdList[res.idx]);
        assert(res.idx == 0);
        assert(res.cnt == 0);
    }
    return true;
}

size_t complressSimplePack1(unsigned char * const pack, const size_t psize, const union DWord * const list, const unsigned char size)
{
    bool    zero = true;
    size_t  len = 0;

    pack[len++] = 0x01;
    pack[len++] = size;
    pack[len++] = 0;
    pack[len++] = 0;
    for(union DWord bit = {.dword=0x80000000}; (0 != bit.dword) && (len < psize); bit.dword>>= 1)
    {
        for(size_t idx=0, max=pack[1]; idx < max; idx ++)
        {
            if( !(list[idx].dword & bit.dword) )
            {
                if(!zero)
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                pack[len] ++;
                if(0xff <= pack[len])
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len++] = 0;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                zero = true;
            }
            else
            {
                if(zero)
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                pack[len] ++;
                if(0xff <= pack[len])
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len++] = 0;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                zero = false;
            }
        }
    }
    if(len < psize)
    {
        len ++;
    }
    pack[2] = static_cast<unsigned char>(len>>8);
    pack[3] = static_cast<unsigned char>(len);
    return len;
}

size_t complressSimpleUnPack1(union DWord * const list, size_t size, const unsigned char * const pack)
{
    bool    zero = true;
    union Word len;
    len.word = pack[2];
    len.word <<= 8;
    len.word |= pack[3];
    if( pack[1] < size )
    {
        size = pack[1];
    }
    for(size_t idx=0, max=size; idx < max; idx ++)
    {
        list[idx].dword = 0;
    }
    union DWord bit = {.dword=0x80000000};
    size_t lidx = 0;
    for(size_t idx=4; idx<len.word; idx++)
    {
        if(zero)
        {
            bit.dword >>= (lidx + pack[idx]) / size;
            lidx = (lidx + pack[idx]) % size;
            zero = false;
        }
        else
        {
            for(size_t cnt=0; cnt<pack[idx]; cnt++)
            {
                list[lidx].dword |= bit.dword;
                lidx ++;
                if(size <= lidx)
                {
                    bit.dword >>= 1;
                    lidx = 0;
                }
            }
            zero = true;
        }
    }
    return size;
}

size_t cpmlessSimple2(unsigned char * const pack, const size_t psize, const union DWord * const list, const unsigned char size)
{
    bool    zero = true;
    size_t  len = 0;

    pack[len++] = 0x01;
    pack[len++] = size;
    pack[len++] = 0;
    pack[len++] = 0;
    for(size_t idx=0, max=pack[1]; idx < max; idx ++)
    {
        for(union DWord bit = {.dword=0x80000000}; (0 != bit.dword) && (len <= psize); bit.dword>>= 1)
        {
            if( !(list[idx].dword & bit.dword) )
            {
                if(!zero)
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                pack[len] ++;
                if(0xff <= pack[len])
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len++] = 0;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                zero = true;
            }
            else
            {
                if(zero)
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                pack[len] ++;
                if(0xff <= pack[len])
                {
                    len ++;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len++] = 0;
                    if(psize <= len)
                    {
                        break;
                    }
                    pack[len] = 0;
                }
                zero = false;
            }
        }
    }
    if(len < psize)
    {
        len ++;
    }
    pack[2] = static_cast<unsigned char>(len>>8);
    pack[3] = static_cast<unsigned char>(len);
    return len;
}

static bool testStage5(void)
{
    cout << "test Stage 5: " << endl;
    static union DWord      list[64];
    static unsigned char    pack[sizeof(list)];
    static union DWord      unpack[256];

    {
        static union DWord test = {.dword = 0xaaaaaaaa};
        for(size_t idx=0, max=(sizeof(list)/sizeof(list[0])); idx < max; idx ++)
        {
            list[idx].dword = test.dword;
//            test.dword ^= 0xffffffff;
        }
        size_t len = complressSimplePack1(pack, sizeof(pack), list, (sizeof(list)/sizeof(list[0])));
        printf( "  len(%d/%d):", static_cast<int>(len), static_cast<int>(sizeof(list)));
        for(size_t idx=0; idx < len; idx ++)
        {
            printf("%02X ",pack[idx]);
        }
        printf("\n");
        if(len < sizeof(pack))
        {
            len = complressSimpleUnPack1(unpack, (sizeof(unpack)/sizeof(unpack[0])), pack);
            assert(0 == memcmp(list, unpack, sizeof(list)));
        }
    }
    {
        for(size_t idx=0, max=(sizeof(list)/sizeof(list[0])); idx < max; idx ++)
        {
            list[idx].dword = idx;
        }
        size_t len = cpmlessSimple2(pack, sizeof(pack), list, (sizeof(list)/sizeof(list[0])));
        printf( "  len(%d/%d):", static_cast<int>(len), static_cast<int>(sizeof(list)));
        for(size_t idx=0; idx < len; idx ++)
        {
            printf("%02X ",pack[idx]);
        }
        printf("\n");
    }
    return true;
}

int main(int argc, char * argv[])
{
    cout << "MyUtilities Software Testting." << endl;
    puts( scrClear );
    printf("%s%sBlack - White%s%s\n", fontBlack, fontWhiteBack, fontWhite, fontBlackBack);
    puts(fontReset);
    assert(testStage1());
    assert(testStage2());
    assert(testStage3());
    assert(testStage4());
    assert(testStage5());
    cout << "pass." << endl;
    cout << endl;
    cout << "test" << endl;
    return 0;
}
