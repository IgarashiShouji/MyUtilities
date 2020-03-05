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
        inline signed int compere(const char * & src) const;
        inline signed int compere(const ConstCString & obj) const;
        inline bool operator == (const ConstCString & obj) const;
        inline bool operator < (const ConstCString & obj) const;
        inline bool operator > (const ConstCString & obj) const;
    };

    template<typename T> class SimpleAllocator
    {
    private:
        size_t *    buffer;
        size_t      buff_cnt;
    public:
        using value_type = T;
        inline SimpleAllocator(void);
        inline SimpleAllocator(size_t * buff, size_t cnt);
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
        union Word
        {
            unsigned short hex;
            struct
            {
                unsigned char lo;
                unsigned char hi;
            } byte;
        };
        const unsigned short * tbl;
        union Word crc;
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
    public:
        class DataRecordIndex
        {
        private:
            struct DataRecordCtrol & obj;
        public:
            inline DataRecordIndex(struct DataRecordCtrol & obj);
            inline ~DataRecordIndex(void);
            inline union DWord & operator [](size_t index);
            inline size_t size(void) const;
        };
    private:
        struct DataRecordCtrol  obj;
        size_t                  id;
        DataRecordIndex         obj_idx;
    public:
        inline DataRecord(size_t recid, union DWord * buff, const size_t * const * ids, const size_t * const * trs, const size_t (* cnt)[8]);
        inline DataRecord(DataRecord & src);
        inline ~DataRecord(void);
        inline void init(size_t recid, union DWord * buff, const size_t * const * ids, const size_t * const * trs, const size_t (* cnt)[8]);
        inline struct DataRecordCtrol & refDataRecordCtrol(void);
        inline size_t recid(void) const;
        inline size_t size(void) const;
        inline size_t byte_size(void) const;
        inline union DWord & operator [](size_t key);
        inline DataRecord & operator = (const DataRecord & src);
        inline DataRecordIndex & ref(void);
        inline const size_t * keys(void) const;
#if __x86_64__
        inline void setListData(const size_t * list, const unsigned int * data, size_t size);
        inline void setListData(const size_t * list, const signed int * data, size_t size);
#else
        inline void setListData(const size_t * list, const unsigned long * data, size_t size);
        inline void setListData(const size_t * list, const signed long * data, size_t size);
#endif
        inline void setListData(const size_t * list, const float * data, size_t size);
        inline void setListData(const size_t * list, const unsigned short * data, size_t size);
        inline void setListData(const size_t * list, const signed short * data, size_t size);
        inline void setListData(const size_t * list, const unsigned char * data, size_t size);
        inline void setListData(const size_t * list, const signed char * data, size_t size);
    };

    /**
     * Data record data stream process class
     */
    class DataRecordStream
    {
    public:
        enum Endian
        {
            big_endian,
            little_endian
        };
    private:
        MyEntity::DataRecord &  rec;
        struct RecStreamCtrl    stm;
        enum Endian             endian;
    public:
        inline DataRecordStream(MyEntity::DataRecord & rec);
        inline ~DataRecordStream(void);
        inline void clear(void);
        inline size_t size(void) const;
        inline bool setEndian(enum Endian endian);
        inline enum DataRecordStream::Endian getEndian(void) const;
        inline size_t index(void) const;
        inline DataRecordStream & operator << (const unsigned char data);
        inline unsigned char get(void);
        inline void seekParam(size_t idx);
    };

    class DataRecCompera
    {
    private:
        struct RecStreamCtrl    self;
    public:
        inline DataRecCompera(MyEntity::DataRecord & rec);
        inline ~DataRecCompera(void);
        inline signed int compre(MyEntity::DataRecord & target);
        inline bool operator == (MyEntity::DataRecord & target);
        inline bool operator > (MyEntity::DataRecord & target);
        inline bool operator < (MyEntity::DataRecord & target);
    };

    class DataRecordInitTables
    {
    private:
        const size_t *          uint32_list;
        const size_t *          int32_list;
        const size_t *          float_list;
        const size_t *          uint16_list;
        const size_t *          int16_list;
        const size_t *          uint8_list;
        const size_t *          int8_list;
#if __x86_64__
        const unsigned int *    uint32_data;
        const signed int *      int32_data;
#else
        const unsigned long *   uint32_data;
        const signed long *     int32_data;
#endif
        const float *           float_data;
        const unsigned short *  uint16_data;
        const signed short *    int16_data;
        const unsigned char *   uint8_data;
        const signed char *     int8_data;
        size_t                  uint32_size;
        size_t                  int32_size;
        size_t                  float_size;
        size_t                  uint16_size;
        size_t                  int16_size;
        size_t                  uint8_size;
        size_t                  int8_size;
    public:
#if __x86_64__
        inline DataRecordInitTables(const size_t * uint32_list, const size_t * int32_list, const size_t * float_list, const size_t * uint16_list, const size_t * int16_list, const size_t * uint8_list, const size_t * int8_list, const unsigned int * uint32_data, const signed int * int32_data, const float * float_data, const unsigned short * uint16_data, const signed short * int16_data, const unsigned char * uint8_data, const signed char * int8_data, size_t uint32_size, size_t int32_size, size_t float_size, size_t uint16_size, size_t int16_size, size_t uint8_size, size_t int8_size);
#else
        inline DataRecordInitTables(const size_t * uint32_list, const size_t * int32_list, const size_t * float_list, const size_t * uint16_list, const size_t * int16_list, const size_t * uint8_list, const size_t * int8_list, const unsigned long * uint32_data, const signed long * int32_data, const float * float_data, const unsigned short * uint16_data, const signed short * int16_data, const unsigned char * uint8_data, const signed char * int8_data, size_t uint32_size, size_t int32_size, size_t float_size, size_t uint16_size, size_t int16_size, size_t uint8_size, size_t int8_size);
#endif
        inline DataRecordInitTables(const DataRecordInitTables & src);
        inline ~DataRecordInitTables(void);
        inline void setData(DataRecord & rec);
    };


    /* -----<< Array Utilitis >>----- */
    template<typename T> inline size_t getIndexArray(const T * list, size_t count, T target)
    {
        size_t top=0;
        for(size_t len=count; 0<len; len = len>>1)
        {
            size_t mid = top + (len>>1);
            auto   val = list[mid];
            if(val == target)
            {
                return mid;
            }
            if(val < target)
            {
                top = mid;
                if(1&len)
                {
                    val = list[top+(len>>1)];
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
            auto obj(arry[mid]);
            auto result = target.compere(obj);
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
                    auto obj(arry[idx]);
                    auto result = target.compere(obj);
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
        return list[count - (1 + idx)];
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
            idx = count - (1 + idx);
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
        if(nullptr == list)
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
        if(nullptr == list)
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
        idx = count - (1 + idx);
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
            idx = count - (1 + idx);
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
    ConstCString::ConstCString(void)
        : str(nullptr), len(0)
    {
    }

    ConstCString::ConstCString(const ConstCString & src)
        : str(src.str), len(src.len)
    {
    }

    ConstCString::ConstCString(const char * _str, size_t size)
        : str(_str), len(size)
    {
        if(nullptr == str)
        {
            len = 0;
        }
    }

    ConstCString::~ConstCString(void)
    {
    }

    const char * ConstCString::c_str(void) const
    {
        return str;
    }

    size_t ConstCString::size(void) const
    {
        return len;
    }

    size_t ConstCString::strLength(void)
    {
        len = strlen(str);
        return len;
    }

    signed int ConstCString::compere(const char * & str) const
    {
        return strcmp(this->str, str);
    }

    signed int ConstCString::compere(const ConstCString & obj) const
    {
        return strcmp(str, obj.c_str());
    }

    bool ConstCString::operator == (const ConstCString & obj) const
    {
        if(0 == compere(obj))
        {
            return true;
        }
        return false;
    }

    bool ConstCString::operator < (const ConstCString & obj) const
    {
        if(compere(obj) < 0)
        {
            return true;
        }
        return false;
    }

    bool ConstCString::operator > (const ConstCString & obj) const
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

    template<typename T> SimpleAllocator<T>::SimpleAllocator(size_t * buff, size_t cnt)
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
        auto    idx  = buffer[0];
        auto *  ptr  = reinterpret_cast<T *>(&buffer[idx]);
        size_t  size = num * sizeof(T);
        idx += (size / sizeof(buffer[0]));
        if(0 != (size % sizeof(buffer[0])))
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
    CalcCRC16::CalcCRC16(void)
        : crc({0xffff}), tbl(nullptr)
    {
    }

    CalcCRC16::CalcCRC16(const unsigned short * crc_tbl)
        : crc({0xffff}), tbl(crc_tbl)
    {
    }

    CalcCRC16::CalcCRC16(CalcCRC16 & src)
        : crc(src.crc), tbl(src.tbl)
    {
    }

    CalcCRC16::~CalcCRC16(void)
    {
        crc.hex = 0xffff;
        tbl     = nullptr;
    }

    CalcCRC16 & CalcCRC16::operator = (CalcCRC16 & src)
    {
        crc.hex = src.crc.hex;
        tbl     = src.tbl;
        return (*this);
    }

    unsigned short CalcCRC16::operator * (void) const
    {
        union Word result;
        result.byte.hi = crc.byte.lo;
        result.byte.lo = crc.byte.hi;
        return result.hex;
    }

    CalcCRC16 & CalcCRC16::operator << (const unsigned char data)
    {
        if(nullptr != tbl)
        {
            union Word val;
            auto idx    = crc.byte.lo ^ data;
            val.hex     = tbl[idx];
            crc.byte.lo = crc.byte.hi ^ val.byte.hi;
            crc.byte.hi = val.byte.lo;
        }
        return (*this);
    }

    /* -----<< Data record >>----- */
    /**
     * Constructor of data record class
     *
     * @param  recid    record id
     * @param  buff     record buffer
     * @param  ids      list of data id
     * @param  trs      list of access saqueance
     * @param  cnt      data count list. cnt[0]: all item, cnt[1]: uint32, cnt[2]: int32, cnt[3]: float, cnt[4]: uint16, cnt[5]: int16, cnt[6]: uint8, cnt[7]: int8
     */
    DataRecord::DataRecord(size_t recid, union DWord * buff, const size_t * const * ids, const size_t * const * trs, const size_t (* cnt)[8])
      : obj_idx(obj)
    {
        init(recid, buff, ids, trs, cnt);
    }
    DataRecord::DataRecord(DataRecord & src)
      : id(src.id), obj(src.obj), obj_idx(obj)
    {
    }
    DataRecord::~DataRecord(void)
    {
    }
    void DataRecord::init(size_t recid, union DWord * buff, const size_t * const * ids, const size_t * const * trs, const size_t (* cnt)[8])
    {
        this->id = recid;
        RecCtrl_init(&obj, buff, ids[id], trs[id], cnt[id]);
    }
    struct DataRecordCtrol & DataRecord::refDataRecordCtrol(void)
    {
        return obj;
    }
    size_t DataRecord::recid(void) const
    {
        return id;
    }
    size_t DataRecord::size(void) const
    {
        return obj.cnts[0];
    }
    size_t DataRecord::byte_size(void) const
    {
        return obj.size;
    }
    union DWord & DataRecord::operator [](size_t key)
    {
        auto item = RecCtrl_get(&obj, key);
        return *item;
    }
    DataRecord & DataRecord::operator = (const DataRecord & src)
    {
        RecCtrl_copy(&(obj), &(src.obj));
        return *this;
    }
    DataRecord::DataRecordIndex & DataRecord::ref(void)
    {
        return obj_idx;
    }
    const size_t * DataRecord::keys(void) const
    {
        return obj.fmt;
    }
#if __x86_64__
    void DataRecord::setListData(const size_t * list, const unsigned int * data, size_t size)
#else
    void DataRecord::setListData(const size_t * list, const unsigned long * data, size_t size)
#endif
    {
         RecCtrl_setListUInt32(&obj, list, data, size);
    }
#if __x86_64__
    void DataRecord::setListData(const size_t * list, const signed int * data, size_t size)
#else
    void DataRecord::setListData(const size_t * list, const signed long * data, size_t size)
#endif
    {
        RecCtrl_setListInt32(&obj, list, data, size);
    }
    void DataRecord::setListData(const size_t * list, const float * data, size_t size)
    {
        RecCtrl_setListFloat(&obj, list, data, size);
    }
    void DataRecord::setListData(const size_t * list, const unsigned short * data, size_t size)
    {
        RecCtrl_setListUInt16(&obj, list, data, size);
    }
    void DataRecord::setListData(const size_t * list, const signed short * data, size_t size)
    {
        RecCtrl_setListInt16(&obj, list, data, size);
    }
    void DataRecord::setListData(const size_t * list, const unsigned char * data, size_t size)
    {
        RecCtrl_setListUInt8(&obj, list, data, size);
    }
    void DataRecord::setListData(const size_t * list, const signed char * data, size_t size)
    {
        RecCtrl_setListInt8(&obj, list, data, size);
    }
    DataRecord::DataRecordIndex::DataRecordIndex(struct DataRecordCtrol & obj_)
      : obj(obj_)
    {
    }
    DataRecord::DataRecordIndex::~DataRecordIndex(void)
    {
    }
    union DWord & DataRecord::DataRecordIndex::operator [](size_t index)
    {
        auto item = RecCtrl_getIndex(&obj, index);
        return *item;
    }
    size_t DataRecord::DataRecordIndex::size(void) const
    {
        return obj.cnts[0];
    }

    /* -----<< Data record data stream process class >>----- */
    /**
     * Constructor
     *
     * @param  record        data record class
     */
    DataRecordStream::DataRecordStream(MyEntity::DataRecord & record)
      : rec(record), endian(big_endian)
    {
        RecStreamCtrl_init(&stm, &(rec.refDataRecordCtrol()));
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
        RecStreamCtrl_init(&stm, &(rec.refDataRecordCtrol()));
    }
    /**
     * max size
     */
    size_t DataRecordStream::size(void) const
    {
        auto result = RecStreamCtrl_Size(&stm);
        return result;
    }
    bool DataRecordStream::setEndian(enum Endian endian)
    {
        if(this->endian != endian)
        {
            this->endian = endian;
            return true;
        }
        return false;
    }
    enum DataRecordStream::Endian DataRecordStream::getEndian(void) const
    {
        return endian;
    }
    size_t DataRecordStream::index(void) const
    {
        return stm.index;
    }

    DataRecordStream & DataRecordStream::operator << (const unsigned char data)
    {
        static void (* const func[2])(struct RecStreamCtrl *, unsigned char) = {RecStreamCtrl_in, RecStreamCtrl_inl};
        (func[endian])(&stm, data);
        return *this;
    }

    unsigned char DataRecordStream::get(void)
    {
        static unsigned char (* const func[2])(struct RecStreamCtrl *) = {RecStreamCtrl_get, RecStreamCtrl_getl};
        auto result = (func[endian])(&stm);
        return result;
    }

    void DataRecordStream::seekParam(size_t idx)
    {
        RecStreamCtrl_seekPram(&stm, idx);
    }

    DataRecCompera::DataRecCompera(MyEntity::DataRecord & rec)
    {
        RecStreamCtrl_init(&self, &(rec.refDataRecordCtrol()));
    }
    DataRecCompera::~DataRecCompera(void)
    {
    }
    signed int DataRecCompera::compre(MyEntity::DataRecord & target)
    {
        struct RecStreamCtrl stm;
        RecStreamCtrl_init(&stm, &(target.refDataRecordCtrol()));
        auto result = RecStreamCtrl_compere(&self, &stm);
        return result;
    }
    bool DataRecCompera::operator == (MyEntity::DataRecord & target)
    {
        if(0 == compre(target))
        {
            return true;
        }
        return false;
    }
    bool DataRecCompera::operator > (MyEntity::DataRecord & target)
    {
        if(0 > compre(target))
        {
            return true;
        }
        return false;
    }
    bool DataRecCompera::operator < (MyEntity::DataRecord & target)
    {
        if(0 < compre(target))
        {
            return true;
        }
        return false;
    }

#if __x86_64__
    DataRecordInitTables::DataRecordInitTables(const size_t * uint32_list_, const size_t * int32_list_, const size_t * float_list_, const size_t * uint16_list_, const size_t * int16_list_, const size_t * uint8_list_, const size_t * int8_list_, const unsigned int * uint32_data_, const signed int * int32_data_, const float * float_data_, const unsigned short * uint16_data_, const signed short * int16_data_, const unsigned char * uint8_data_, const signed char * int8_data_, size_t uint32_size_, size_t int32_size_, size_t float_size_, size_t uint16_size_, size_t int16_size_, size_t uint8_size_, size_t int8_size_)
#else
    DataRecordInitTables::DataRecordInitTables(const size_t * uint32_list_, const size_t * int32_list_, const size_t * float_list_, const size_t * uint16_list_, const size_t * int16_list_, const size_t * uint8_list_, const size_t * int8_list_, const unsigned long * uint32_data_, const signed long * int32_data_, const float * float_data_, const unsigned short * uint16_data_, const signed short * int16_data_, const unsigned char * uint8_data_, const signed char * int8_data_, size_t uint32_size_, size_t int32_size_, size_t float_size_, size_t uint16_size_, size_t int16_size_, size_t uint8_size_, size_t int8_size_)
#endif
      : uint32_list(uint32_list_), int32_list(int32_list_), float_list(float_list_), uint16_list(uint16_list_), int16_list(int16_list_), uint8_list(uint8_list_), int8_list(int8_list_), uint32_data(uint32_data_), int32_data(int32_data_), float_data(float_data_), uint16_data(uint16_data_), int16_data(int16_data_), uint8_data(uint8_data_), int8_data(int8_data_), uint32_size(uint32_size_), int32_size(int32_size_), float_size(float_size_), uint16_size(uint16_size_), int16_size(int16_size_), uint8_size(uint8_size_), int8_size(int8_size_)
    {
    }
    DataRecordInitTables::DataRecordInitTables(const DataRecordInitTables & src)
      : uint32_list(src.uint32_list), int32_list(src.int32_list), float_list(src.float_list), uint16_list(src.uint16_list), int16_list(src.int16_list), uint8_list(src.uint8_list), int8_list(src.int8_list), uint32_data(src.uint32_data), int32_data(src.int32_data), float_data(src.float_data), uint16_data(src.uint16_data), int16_data(src.int16_data), uint8_data(src.uint8_data), int8_data(src.int8_data), uint32_size(src.uint32_size), int32_size(src.int32_size), float_size(src.float_size), uint16_size(src.uint16_size), int16_size(src.int16_size), uint8_size(src.uint8_size), int8_size(src.int8_size)
    {
    }
    DataRecordInitTables::~DataRecordInitTables(void)
    {
    }

    void DataRecordInitTables::setData(DataRecord & rec)
    {
        rec.setListData(uint32_list, uint32_data, uint32_size);
        rec.setListData(int32_list, int32_data, int32_size);
        rec.setListData(float_list, float_data, float_size);
        rec.setListData(uint16_list, uint16_data, uint16_size);
        rec.setListData(int16_list, int16_data, int16_size);
        rec.setListData(uint8_list, uint8_data, uint8_size);
        rec.setListData(int8_list, int8_data, int8_size);
    }
};


#endif
