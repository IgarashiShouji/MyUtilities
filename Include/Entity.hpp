/**
 * utilities file of C++ language
 *
 * @file Entity.hpp
 * @brief C++ Entity Utilitis
 * @author Shouji, Igarashi
 *
 * (c) 2018 Shouji, Igarashi.
 */

#ifndef __Entity_hpp__
#define __Entity_hpp__

extern "C"
{
#include "MyUtilities.h"
}
#include <stdlib.h>
#include <string.h>

namespace MyEntity
{
    /**
     * Const Array Data Class
     *
     */
    template<typename T> class ConstArray
    {
    private:
        /**
         * data list pointer
         */
        const T *   list;
        /**
         * data list count
         */
        size_t      count;
    public:
        inline ConstArray(void);
        inline ConstArray(const ConstArray & obj);
        inline ConstArray(const ConstArray & obj, size_t start);
        inline ConstArray(const T * _list, size_t cnt);
        inline ~ConstArray(void);
        inline const T * ptr(void) const;
        inline size_t size(void) const;
        inline const T & operator [] (size_t idx) const;
        inline size_t getIndex(const T & target) const;
        inline bool hasValue(const T & target) const;
    };
    typedef ConstArray<unsigned char>  ConstArrayByte;
    typedef ConstArray<unsigned short> ConstArrayShort;
    typedef ConstArray<unsigned int>   ConstArrayInteger;

    /**
     * Const Array Reverse Access Data Class
     *
     */
    template<typename T> class ConstArrayR
    {
    private:
        /**
         * data list pointer
         */
        const T *   list;
        /**
         * data list count
         */
        size_t      count;
    public:
        inline ConstArrayR(void);
        inline ConstArrayR(const ConstArrayR & obj);
        inline ConstArrayR(const T * _list, size_t cnt);
        inline ~ConstArrayR(void);
        inline const T * ptr(void) const;
        inline size_t size(void) const;
        inline const T & operator [] (size_t idx) const;
        inline size_t getIndex(const T & target) const;
        inline bool hasValue(const T & target) const;
    };
    typedef ConstArrayR<unsigned char>  ConstArrayByteR;
    typedef ConstArrayR<unsigned short> ConstArrayShortR;
    typedef ConstArrayR<unsigned int>   ConstArrayIntegerR;

    /**
     * Array Data Class
     *
     */
    template<typename T> class Array
    {
    private:
        /**
         * data list pointer
         */
        T *         list;
        /**
         * data list count
         */
        size_t      count;
    public:
        inline Array(void);
        inline Array(Array& obj);
        inline Array(T * _list, size_t cnt);
        inline ~Array(void);
        inline T * ptr(void);
        inline size_t size(void) const;
        inline T & operator [] (size_t idx);
        inline size_t getIndex(T target) const;
        inline bool hasValue(const T & target) const;
        inline Array<T> & operator = (ConstArray<T> & src);
        inline Array<T> & operator = (Array<T> & src);
    };
    typedef Array<unsigned char>  ArrayByte;
    typedef Array<unsigned short> ArrayShort;
    typedef Array<unsigned int>   ArrayInteger;

    /**
     * Array Reverse Data Class
     *
     */
    template<typename T> class ArrayR
    {
    private:
        /**
         * data list pointer
         */
        T *         list;
        /**
         * data list count
         */
        size_t      count;
    public:
        inline ArrayR(void);
        inline ArrayR(ArrayR & obj);
        inline ArrayR(T * _list, size_t cnt);
        inline ~ArrayR(void);
        inline T * ptr(void);
        inline size_t size(void) const;
        inline T & operator [] (size_t idx);
        inline size_t getIndex(T target) const;
        inline bool hasValue(const T & target) const;
        inline ArrayR<T> & operator = (ConstArrayR<T> & src);
        inline ArrayR<T> & operator = (ArrayR<T> & src);
    };
    typedef ArrayR<unsigned char>  ArrayByteR;
    typedef ArrayR<unsigned short> ArrayShortR;
    typedef ArrayR<unsigned int>   ArrayIntegerR;

    /**
     * mapping of Const Array and Array list
     *
     */
    template<typename T1, typename T2> class ConstArrayMap
    {
    private:
        /**
         * data list pointer
         */
        T1 *        list;
        /**
         * key list pointer
         */
        const T2 *  keys;
        /**
         * data list count
         */
        size_t      count;
    public:
        inline ConstArrayMap(T1 * data, const T2 * keys, size_t cnt);
        inline ConstArrayMap(ConstArrayMap & src);
        inline ~ConstArrayMap(void);
        inline size_t size(void) const;
        inline size_t getIndex(const T2 & key) const;
        inline const T2 & getKey(size_t idx) const;
        inline const T1 getItem(size_t idx) const;
        inline T1 getItem(size_t idx);
        inline const T1 & operator [](const T2 & key) const;
        inline T1 & operator [](const T2 & key);
        inline size_t copy(const ConstArrayMap<T1, T2> & src);
        inline ConstArrayMap<T1, T2> & operator = (const ConstArrayMap<T1, T2> & src);
    };

    template<typename T> class Compere
    {
    public:
        virtual signed int compere(T & src) const = 0;
    };
    class ConstCString : public Compere<const char *>
    {
    private:
        const char *    str;
        size_t          len;
    public:
        inline ConstCString(void);
        inline ConstCString(const ConstCString & src);
        inline ConstCString(const char *, size_t size = 0);
        inline ~ConstCString(void);
        inline const char * c_str(void) const;
        inline size_t size(void) const;
        inline size_t strLength(void);
        virtual signed int compere(const char * & src) const;
        inline signed int compere(const ConstCString & obj) const;
        inline bool operator == (const ConstCString & obj) const;
        inline bool operator < (const ConstCString & obj) const;
        inline bool operator > (const ConstCString & obj) const;
    };

    template<typename T> class SimpleAllocator
    {
    private:
        unsigned long * buffer;
        size_t buff_cnt;
    public:
        using value_type = T;
        inline SimpleAllocator(void);
        inline SimpleAllocator(unsigned long * buff, size_t cnt);
        inline SimpleAllocator(const SimpleAllocator & src);
        inline SimpleAllocator(SimpleAllocator && src);
        template <typename U> SimpleAllocator(const SimpleAllocator<U>&) {}
        inline T* allocate(size_t num);
        inline void deallocate(T* p, size_t num);
        inline void init(void);
        inline size_t count(void);
        inline unsigned long size(void);
    };

    /**
     * CRC16
     */
    class CalcCRC16
    {
    private:
        const unsigned short * tbl;
        union
        {
            unsigned short hex;
            struct
            {
                unsigned char lo;
                unsigned char hi;
            } byte;
        } crc;
    public:
        inline CalcCRC16(void);
        inline CalcCRC16(const unsigned short * crc_tbl);
        inline CalcCRC16(CalcCRC16 & src);
        inline ~CalcCRC16(void);
        inline CalcCRC16 & operator = (CalcCRC16 & src);
        inline CalcCRC16 & operator << (const unsigned char data);
        inline unsigned short operator * (void) const;
        static unsigned short calc(const unsigned char * data, unsigned int size, const unsigned short * crc_tbl);
    };

    /**
     * Data record class
     */
    class DataRecord
    {
    private:
        union DWord *           buff;
        const unsigned short *  ids;
        MyEntity::ConstArrayMap<union DWord, unsigned short> dword;
        MyEntity::ConstArrayMap<union Word,  unsigned short> word;
        MyEntity::ConstArrayMap<union Byte,  unsigned short> byte;
        size_t dwordMaxIDs;
        size_t wordMaxIDs;
        size_t byteMaxIDs;
    public:
        inline DataRecord(union DWord * buff, const unsigned short * ids, const unsigned short * cnt, size_t DwMax, size_t WdMax, size_t ByMax);
        inline DataRecord(union DWord * buff, DataRecord & src);
        inline ~DataRecord(void);
        inline MyEntity::ConstArrayMap<union DWord, unsigned short> & getDWordList(void);
        inline MyEntity::ConstArrayMap<union Word,  unsigned short> & getWordList(void);
        inline MyEntity::ConstArrayMap<union Byte,  unsigned short> & getByteList(void);
        unsigned char dataSize(unsigned short key) const;
        DataRecord & operator = (DataRecord & src);
        union DWord & operator [](unsigned short key);
    };

    /**
     * Data record data stream process class
     */
    class DataRecordStream
    {
    private:
        MyEntity::DataRecord &  rec;
        const unsigned short *  fmt;
        size_t                  idx;
        size_t                  cnt;
        size_t                  max;
        unsigned char           pos;
        unsigned char           dsz;
    public:
        inline DataRecordStream(MyEntity::DataRecord & rec, const unsigned short * fmt, size_t fmtCnt);
        inline ~DataRecordStream(void);
        inline void clear(void);
        inline size_t size(void);
        inline size_t count(void);
        DataRecordStream & operator << (const unsigned char data);
        unsigned char get(void);
    };


    /* -----<< Array Utilitis >>----- */
    template<typename T> inline size_t getIndexArray(const T * list, size_t count, T target)
    {
        size_t top=0;
        for(size_t len=count; 0<len; len = len>>1)
        {
            size_t mid = top + (len>>1);
            T val = list[mid];
            if(val == target)
            {
                return mid;
            }
            if(val < target)
            {
                top = mid;
                if(1&len)
                {
                    T val = list[top+(len>>1)];
                    if(val == target)
                    {
                        return (top+(len>>1));
                    }
                }
            }
        }
        return count;
    }

    template<typename T> inline size_t getIndexArray(const ConstArray<T> & arry, const Compere<T> & target)
    {
        size_t top=0;
        for(size_t len=arry.size(); 0<len; len = len>>1)
        {
            size_t mid = top + (len>>1);
            T obj(arry[mid]);
            signed int result = target.compere(obj);
            if(0 == result)
            {
                return mid;
            }
            if(0 < result)
            {
                top = mid;
                if(1 & len)
                {
                    size_t idx = top + (len>>1);
                    T obj(arry[idx]);
                    signed int result = target.compere(obj);
                    if(0 == result)
                    {
                        return idx;
                    }
                }
            }
        }
        return arry.size();
    }

    template<typename T> void copyArray(T * dst, size_t dst_cnt, const T * src, size_t src_cnt)
    {
        int len=dst_cnt;
        if(src_cnt<len)
        {
            len = src_cnt;
        }
        for(size_t idx=0; idx<len; idx++)
        {
            dst[idx] = src[idx];
        }
    }

    /* -----<< ConstArray >>----- */
    /**
     * Default constructor
     */
    template<typename T> inline ConstArray<T>::ConstArray(void)
        : list(nullptr), count(0)
    {
    }

    /**
     * Copy constructor
     *
     * @param obj    Copy Source Object
     */
    template<typename T> inline ConstArray<T>::ConstArray(const ConstArray & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Copy constructor
     *
     * @param obj    Copy Source Object
     * @param start  Start Position of list
     */
    template<typename T> inline ConstArray<T>::ConstArray(const ConstArray & obj, size_t start)
        : list(&(obj.list[start])), count(obj.count-start)
    {
    }

    /**
     * Construtor with Array List
     *
     * @param _list     Const Array List pointer
     * @param cnt       Array List Count
     */
    template<typename T> inline ConstArray<T>::ConstArray(const T * _list, size_t cnt)
        : list(_list), count(cnt)
    {
        if(nullptr==list)
        {
            count = 0;
        }
    }

    /**
     * Destructor
     *
     */
    template<typename T> inline ConstArray<T>::~ConstArray(void)
    {
    }

    /**
     * get Const Data Array List Pointer
     *
     * @return Const Data Array List Pointer
     */
    template<typename T> inline const T * ConstArray<T>::ptr(void) const
    {
        return list;
    }

    /**
     * Array List Length
     *
     * @return Array List Length
     */
    template<typename T> inline size_t ConstArray<T>::size(void) const
    {
        return count;
    }

    /**
     * refarence data
     *
     * @param  idx       index for Array list
     * @return list data
     */
    template<typename T> inline const T & ConstArray<T>::operator [] (size_t idx) const
    {
        return list[idx];
    }

    /**
     * get Array List Index
     *
     * @param target    search Data
     */
    template<typename T> inline size_t ConstArray<T>::getIndex(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        return idx;
    }

    /**
     * Target Vlue have a Array List
     *
     * @param target    search Data
     */
    template<typename T> inline bool ConstArray<T>::hasValue(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(count == idx)
        {
            return false;
        }
        return true;
    }

    /* -----<< ConstArrayR >>----- */
    /**
     * Default constructor
     */
    template<typename T> inline ConstArrayR<T>::ConstArrayR(void)
        : list(nullptr), count(0)
    {
    }

    /**
     * Copy constructor
     *
     * @param obj    Copy Source Object
     */
    template<typename T> inline ConstArrayR<T>::ConstArrayR(const ConstArrayR & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constructor with Array List
     *
     * @param _list     Const Array List pointer
     * @param cnt       Array List Count
     */
    template<typename T> inline ConstArrayR<T>::ConstArrayR(const T * _list, size_t cnt)
        : list(_list), count(cnt)
    {
        if(nullptr==list)
        {
            count = 0;
        }
    }

    /**
     * Destructor
     *
     */
    template<typename T> inline ConstArrayR<T>::~ConstArrayR(void)
    {
    }

    /**
     * get Const Data Array List Pointer
     *
     * @return Const Data Array List Pointer
     */
    template<typename T> inline const T * ConstArrayR<T>::ptr(void) const
    {
        return list;
    }

    /**
     * Array List Length
     *
     * @return Array List Length
     */
    template<typename T> inline size_t ConstArrayR<T>::size(void) const
    {
        return count;
    }

    /**
     * refarence data
     *
     * @param  idx       index for Array list
     * @return list data
     */
    template<typename T> inline const T & ConstArrayR<T>::operator [] (size_t idx) const
    {
        return list[count-(1+idx)];
    }

    /**
     * get Array List Index
     *
     * @param target    search Data
     */
    template<typename T> inline size_t ConstArrayR<T>::getIndex(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(idx < count)
        {
            idx =count-(1+idx);
        }
        return idx;
    }

    /**
     * target value have a Array List
     *
     * @param target    search Data
     */
    template<typename T> inline bool ConstArrayR<T>::hasValue(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(idx == count)
        {
            return false;
        }
        return true;
    }

    /* -----<< Array Class >>----- */
    /**
     * Default constructor
     *
     */
    template<typename T> inline Array<T>::Array(void)
        : count(0)
    {
    }

    /**
     * Copy constructor
     *
     */
    template<typename T> inline Array<T>::Array(Array & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constructor with Array list
     *
     */
    template<typename T> inline Array<T>::Array(T * _list, size_t cnt)
        : list(_list), count(cnt)
    {
        if(nullptr==list)
        {
            count = 0;
        }
    }

    /**
     * Destructor
     *
     */
    template<typename T> inline Array<T>::~Array(void)
    {
    }

    /**
     * get Array List Pointer
     *
     * @return Array List Pointer
     */
    template<typename T> inline T * Array<T>::ptr(void)
    {
        return list;
    }

    /**
     * Array List Length
     *
     * @return Array List Length
     */
    template<typename T> inline size_t Array<T>::size(void) const
    {
        return count;
    }

    /**
     * refarence data
     *
     * @param  idx       index for Array list
     * @return list data
     */
    template<typename T> inline T & Array<T>::operator [] (size_t idx)
    {
        return list[idx];
    }

    /**
     * get Array List Index
     *
     * @param target    search Data
     */
    template<typename T> inline size_t Array<T>::getIndex(T target) const
    {
        size_t idx = getIndexArray(list, count, target);
        return idx;
    }

    /**
     * Target have a Array List
     *
     * @param target    search Data
     */
    template<typename T> inline bool Array<T>::hasValue(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(count == idx)
        {
            return false;
        }
        return true;
    }

    /**
     * Copy Array Data
     *
     * @param  src      Copy Source Object
     * @return this Object
     */
    template<typename T> inline Array<T> & Array<T>::operator = (ConstArray<T> & src)
    {
        copyArray(list, count, src.ptr(), src.size());
        return (*this);
    }

    /**
     * Copy Array Data
     *
     * @param  src      Copy Source Object
     * @return this Object
     */
    template<typename T> inline Array<T> & Array<T>::operator = (Array<T> & src)
    {
        copyArray(list, count, src.ptr(), src.size());
        return (*this);
    }

    /* -----<< ArrayR Class >>----- */
    /**
     * Default constructor
     *
     */
    template<typename T> inline ArrayR<T>::ArrayR(void)
        : count(0)
    {
    }

    /**
     * Copy constructor
     *
     */
    template<typename T> inline ArrayR<T>::ArrayR(ArrayR & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constructor with ArrayR list
     *
     */
    template<typename T> inline ArrayR<T>::ArrayR(T * _list, size_t cnt)
        : list(_list), count(cnt)
    {
        if(nullptr==list)
        {
            count = 0;
        }
    }

    /**
     * Desutructor
     *
     */
    template<typename T> inline ArrayR<T>::~ArrayR(void)
    {
    }

    /**
     * get ArrayR List Pointer
     *
     * @return ArrayR List Pointer
     */
    template<typename T> inline T * ArrayR<T>::ptr(void)
    {
        return list;
    }

    /**
     * ArrayR List Length
     *
     * @return ArrayR List Length
     */
    template<typename T> inline size_t ArrayR<T>::size(void) const
    {
        return count;
    }

    /**
     * refarence data
     *
     * @param  idx       index for ArrayR list
     * @return list data
     */
    template<typename T> inline T & ArrayR<T>::operator [] (size_t idx)
    {
        idx = count - (1+idx);
        return list[idx];
    }

    /**
     * get ArrayR List Index
     *
     * @param target    search Data
     */
    template<typename T> inline size_t ArrayR<T>::getIndex(T target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(idx < count)
        {
            idx = count - (1+idx);
        }
        return idx;
    }

    /**
     * Target have a Array List
     *
     * @param target    search Data
     */
    template<typename T> inline bool ArrayR<T>::hasValue(const T & target) const
    {
        size_t idx = getIndexArray(list, count, target);
        if(count == idx)
        {
            return false;
        }
        return true;
    }

    /**
     * Copy ArrayR Data
     *
     * @param  src      Copy Source Object
     * @return this Object
     */
    template<typename T> inline ArrayR<T> & ArrayR<T>::operator = (ConstArrayR<T> & src)
    {
        copyArray(list, count, src.ptr(), src.size());
        return (*this);
    }

    /**
     * Copy ArrayR Data
     *
     * @param  src      Copy Source Object
     * @return this Object
     */
    template<typename T> inline ArrayR<T> & ArrayR<T>::operator = (ArrayR<T> & src)
    {
        copyArray(list, count, src.ptr(), src.size());
        return (*this);
    }

    /* -----<< ConstArrayMap >>----- */
    /**
     * Default constractor of mapping array list and const array key list class
     *
     * @param  data     Data Array List
     * @param  key_list Data Key List
     * @param  cnt      Array Count
     */
    template<typename T1, typename T2> ConstArrayMap<T1, T2>::ConstArrayMap(T1 * data, const T2 * key_list, size_t cnt)
      : list(data), keys(key_list), count(cnt)
    {
    }

    /**
     * Copy constractor of Mapping Array list and const Array key list class
     *
     * @param  src      source object
     */
    template<typename T1, typename T2> ConstArrayMap<T1, T2>::ConstArrayMap(ConstArrayMap & src)
      : list(src.list), keys(src.keys), count(src.count)
    {
    }

    /**
     * Desutructor
     */
    template<typename T1, typename T2> ConstArrayMap<T1, T2>::~ConstArrayMap(void)
    {
    }

    /**
     * Get array size(count)
     *
     * @return Array Size
     */
    template<typename T1, typename T2> size_t ConstArrayMap<T1, T2>::size(void) const
    {
        return count;
    }

    /**
     * Get index of key list
     *
     * @param  key      search key object
     * @return index of key list
     */
    template<typename T1, typename T2> size_t ConstArrayMap<T1, T2>::getIndex(const T2 & key) const
    {
        ConstArray<T2> key_list(keys, count);
        return key_list.getIndex(key);
    }

    /**
     * Get key object
     *
     * @param  keyIndex index of key list
     * @return key object
     */
    template<typename T1, typename T2> const T2 & ConstArrayMap<T1, T2>::getKey(size_t keyIndex) const
    {
        return keys[keyIndex];
    }

    /**
     * Get const item object
     *
     * @param  idx      index of item list
     * @return item objecgt
     */
    template<typename T1, typename T2> const T1 ConstArrayMap<T1, T2>::getItem(size_t idx) const
    {
        return list[idx];
    }

    /**
     * Get item object
     *
     * @param  idx      index of item list
     * @return item objecgt
     */
    template<typename T1, typename T2> T1 ConstArrayMap<T1, T2>::getItem(size_t idx)
    {
        return list[idx];
    }

    /**
     * Get item const object
     *
     * @param  key      keyword of item list
     * @return item objecgt
     */
    template<typename T1, typename T2> const T1 & ConstArrayMap<T1, T2>::operator [](const T2 & key) const
    {
        size_t idx = getIndex(key);
        return list[idx];
    }

    /**
     * Get item object
     *
     * @param  key      keyword of item list
     * @return item objecgt
     */
    template<typename T1, typename T2> T1 & ConstArrayMap<T1, T2>::operator [](const T2 & key)
    {
        size_t idx = getIndex(key);
        return list[idx];
    }

    /**
     * copy of ConstArrayMap
     *
     * @param  src      Copy Source Object
     * @return Copy Count
     */
    template<typename T1, typename T2> size_t ConstArrayMap<T1, T2>::copy(const ConstArrayMap<T1, T2> & src)
    {
        size_t cnt = 0;
        if(size() <= src.size())
        {
            for(size_t idx=0, max=size(); idx < max; idx ++)
            {
                size_t src_idx = src.getIndex(keys[idx]);
                if(src_idx < src.size())
                {
                    list[idx] = src.getItem(src_idx);
                    cnt ++;
                }
            }
        }
        else
        {
            for(size_t src_idx=0, max=src.size(); src_idx < max; src_idx ++)
            {
                size_t idx = getIndex(src.getKey(src_idx));
                if(idx < size())
                {
                    list[idx] = src.getItem(src_idx);
                    cnt ++;
                }
            }
        }
        return cnt;
    }

    /**
     * copy of ConstArrayMap
     *
     * @param  src      Copy Source Object
     * @return this Object
     */
    template<typename T1, typename T2> ConstArrayMap<T1, T2> & ConstArrayMap<T1, T2>::operator = (const ConstArrayMap<T1, T2> & src)
    {
        this->copy(src);
        return *this;
    }

    /* -----<< ConstCString >>----- */
    inline ConstCString::ConstCString(void)
        : str(nullptr), len(0)
    {
    }

    inline ConstCString::ConstCString(const ConstCString & src)
        : str(src.str), len(src.len)
    {
    }

    inline ConstCString::ConstCString(const char * _str, size_t size)
        : str(_str), len(size)
    {
        if(nullptr==str)
        {
            len = 0;
        }
    }

    inline ConstCString::~ConstCString(void)
    {
    }

    inline const char * ConstCString::c_str(void) const
    {
        return str;
    }

    inline size_t ConstCString::size(void) const
    {
        return len;
    }

    inline size_t ConstCString::strLength(void)
    {
        len = strlen(str);
        return len;
    }

    inline signed int ConstCString::compere(const ConstCString & obj) const
    {
        return strcmp(str, obj.c_str());
    }

    inline bool ConstCString::operator == (const ConstCString & obj) const
    {
        if(compere(obj) == 0)
        {
            return true;
        }
        return false;
    }

    inline bool ConstCString::operator < (const ConstCString & obj) const
    {
        if(compere(obj) < 0)
        {
            return true;
        }
        return false;
    }

    inline bool ConstCString::operator > (const ConstCString & obj) const
    {
        if(compere(obj) > 0)
        {
            return true;
        }
        return false;
    }

    /* -----<< SimpleAllocator >>----- */
    template<typename T> SimpleAllocator<T>::SimpleAllocator(void)
    {
    }

    template<typename T> SimpleAllocator<T>::SimpleAllocator(unsigned long * buff, size_t cnt)
      : buffer(buff), buff_cnt(cnt)
    {
    }

    template<typename T> SimpleAllocator<T>::SimpleAllocator(const SimpleAllocator & src)
      : buffer(src.buffer), buff_cnt(src.buff_cnt)
    {
    }

    template<typename T> SimpleAllocator<T>::SimpleAllocator(SimpleAllocator && src)
      : buffer(src.buffer), buff_cnt(src.buff_cnt)
    {
    }

    template<typename T> T * SimpleAllocator<T>::allocate(size_t num)
    {
        unsigned long idx = buffer[0];
        T * ptr = reinterpret_cast<T*>(&buffer[idx]);
        size_t size = num * sizeof(T);
        idx += (size / sizeof(unsigned long));
        if(0 != (size % sizeof(unsigned long)))
        {
            idx ++;
        }
        buffer[0] = idx;
        return ptr;
    }

    template<typename T> void SimpleAllocator<T>::deallocate(T* p, size_t num)
    {
    }

    template<typename T> void SimpleAllocator<T>::init(void)
    {
        buffer[0] = 1;
    }

    template<typename T> size_t SimpleAllocator<T>::count(void)
    {
        return buff_cnt;
    }
    template<typename T> unsigned long SimpleAllocator<T>::size(void)
    {
        return buffer[0];
    }


    template <typename T1, typename T2> bool operator==(const SimpleAllocator<T1>&, const SimpleAllocator<T2>&)
    {
        return true;
    }

    template <typename T1, typename T2> bool operator!=(const SimpleAllocator<T1>&, const SimpleAllocator<T2>&)
    {
        return false;
    }

    /* -----<< CalcCRC16 >>----- */
    inline CalcCRC16::CalcCRC16(void)
        : crc({0xffff}), tbl(nullptr)
    {
    }

    inline CalcCRC16::CalcCRC16(const unsigned short * crc_tbl)
        : crc({0xffff}), tbl(crc_tbl)
    {
    }

    inline CalcCRC16::CalcCRC16(CalcCRC16 & src)
        : crc(src.crc), tbl(src.tbl)
    {
    }

    inline CalcCRC16::~CalcCRC16(void)
    {
        crc.hex = 0xffff;
        tbl     = nullptr;
    }

    inline CalcCRC16 & CalcCRC16::operator = (CalcCRC16 & src)
    {
        crc.hex = src.crc.hex;
        tbl     = src.tbl;
        return (*this);
    }

    inline unsigned short CalcCRC16::operator * (void) const
    {
        unsigned short result  = static_cast<unsigned short>(crc.byte.lo)<<8;
                       result |= static_cast<unsigned short>(crc.byte.hi);
        return result;
    }

    inline CalcCRC16 & CalcCRC16::operator << (const unsigned char data)
    {
        if(nullptr!=tbl)
        {
            unsigned int uIndex = crc.byte.lo ^ data;
            unsigned short val = tbl[uIndex];
            crc.byte.lo = crc.byte.hi ^ static_cast<unsigned char>(val>>8);
            crc.byte.hi = static_cast<unsigned char>(val);
        }
        return (*this);
    }

    /* -----<< Data record >>----- */
    /**
     * Constructor of data record class
     *
     * @param  buffer   container of data record items.
     * @param  id_list  data ids list in data record.
     * @param  cnt      data count list. cnt[0]: all item count / cnt[1]: 4 byte count / cnt[2]: 2 byte count / cnt[3]: 1 byte count
     */
    DataRecord::DataRecord(union DWord * buffer, const unsigned short * id_list, const unsigned short * cnt, size_t DwMax, size_t WdMax, size_t ByMax)
      : buff(buffer), ids(id_list), dword(&(buff[0]), &(ids[0]), cnt[1]), word(&(buff[cnt[1]].words[0]), &(ids[cnt[1]]), cnt[2]), byte(&(buff[cnt[1]+cnt[2]].bytes[0]), &(ids[cnt[1]+cnt[2]]), cnt[3]), dwordMaxIDs(DwMax), wordMaxIDs(WdMax), byteMaxIDs(ByMax)
    {
    }

    DataRecord::DataRecord(union DWord * buffer, DataRecord & src)
      : buff(buffer), ids(src.ids), dword(src.dword), word(src.word), byte(src.byte), dwordMaxIDs(src.dwordMaxIDs), wordMaxIDs(src.wordMaxIDs), byteMaxIDs(byteMaxIDs)
    {
    }

    /**
     * Desutructor of data record class
     */
    DataRecord::~DataRecord(void)
    {
    }

    /**
     * Get mapping class of "union DWord" data list
     *
     * @return mapping object of "union DWord" data list
     */
    MyEntity::ConstArrayMap<union DWord, unsigned short> & DataRecord::getDWordList(void)
    {
        return dword;
    }

    /**
     * Get mapping class of "union Word" data list
     *
     * @return mapping object of "union Word" data list
     */
    MyEntity::ConstArrayMap<union Word,  unsigned short> & DataRecord::getWordList(void)
    {
        return word;
    }

    /**
     * Get mapping class of "union Byte" data list
     *
     * @return mapping object of "union Byte" data list
     */
    MyEntity::ConstArrayMap<union Byte,  unsigned short> & DataRecord::getByteList(void)
    {
        return byte;
    }

    /* -----<< Data record data stream process class >>----- */
    /**
     * Constructor
     *
     * @param  record        data record class
     * @param  format        data item stream list
     * @param  formatCount   data item stream list Count
     */
    DataRecordStream::DataRecordStream(MyEntity::DataRecord & record, const unsigned short * format, size_t formatCount)
      : rec(record), fmt(format)
    {
        max = 0;
        for(size_t idx=0; idx<formatCount; idx++)
        {
            max += rec.dataSize(fmt[idx]);
        }
        clear();
    }

    /**
     * Destructor
     */
    DataRecordStream::~DataRecordStream(void)
    {
    }

    /**
     * clear status
     */
    void DataRecordStream::clear(void)
    {
        idx = 0;
        cnt = 0;
        pos = 0;
        dsz = rec.dataSize(fmt[idx]);
    }
    /**
     * max size
     */
    size_t DataRecordStream::size(void)
    {
        return max;
    }

    /**
     * count
     */
    size_t DataRecordStream::count(void)
    {
        return cnt;
    }
};


#endif
