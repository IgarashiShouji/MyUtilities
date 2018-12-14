/**
 * Entity Class File
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
     * Default Constractor
     */
    template<typename T> inline ConstArray<T>::ConstArray(void)
        : list(nullptr), count(0)
    {
    }

    /**
     * Copy Constructor
     *
     * @param obj    Copy Source Object
     */
    template<typename T> inline ConstArray<T>::ConstArray(const ConstArray & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Copy Constructor
     *
     * @param obj    Copy Source Object
     * @param start  Start Position of list
     */
    template<typename T> inline ConstArray<T>::ConstArray(const ConstArray & obj, size_t start)
        : list(&(obj.list[start])), count(obj.count-start)
    {
    }

    /**
     * Constractor with Array List
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
     * Destractor
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
     * Default Constractor
     */
    template<typename T> inline ConstArrayR<T>::ConstArrayR(void)
        : list(nullptr), count(0)
    {
    }

    /**
     * Copy Constructor
     *
     * @param obj    Copy Source Object
     */
    template<typename T> inline ConstArrayR<T>::ConstArrayR(const ConstArrayR & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constractor with Array List
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
     * Destractor
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
     * Default Constractor
     *
     */
    template<typename T> inline Array<T>::Array(void)
        : count(0)
    {
    }

    /**
     * Copy Constractor
     *
     */
    template<typename T> inline Array<T>::Array(Array & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constractor with Array list
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
     * Destractor
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
     * Default Constractor
     *
     */
    template<typename T> inline ArrayR<T>::ArrayR(void)
        : count(0)
    {
    }

    /**
     * Copy Constractor
     *
     */
    template<typename T> inline ArrayR<T>::ArrayR(ArrayR & obj)
        : list(obj.list), count(obj.count)
    {
    }

    /**
     * Constractor with ArrayR list
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
     * Destractor
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
     * Destractor
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
     * @param  idx      index of item list
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
     * @param  idx      index of item list
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
};


#endif
