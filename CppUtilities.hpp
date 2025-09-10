#ifndef cpp_utilities_hpp
#define cpp_utilities_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <thread>
#include <mutex>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <filesystem>


/* ----------------------------------------------------------------------------< My Library >---------------------------------------------------------------------------- */
/**
 * Value Continer
 */
class ClsValue
{
public:
    enum Type_v
    {
        /* 8 byte data */
        type_uint64,
        type_int64,
        type_double,

        /* 4 byte data */
        type_uint32,
        type_int32,
        type_float,

        /* 2 byte data */
        type_uint16,
        type_int16,

        /* 1 byte data */
        type_uint8,
        type_int8,
        type_char,

        /* string data */
        type_str,

        /* unkown data */
        type_none
    };
    union vData
    {
        uint8_t         uint8;
        int8_t          int8;
        uint16_t        uint16;
        int16_t         int16;
        uint32_t        uint32;
        int32_t         int32;
        uint64_t        uint64;
        int64_t         int64;
        float           v_float;
        double          v_double;
        char            ch;

        unsigned int    data;
        signed int      value;
        uint8_t         buff[sizeof(double)];
    };
private:
    Type_v      type;
    vData       data;
    std::string dstr;
public:
    inline ClsValue(void)            : type(type_none),   dstr("") { data.data     = 0;   }
    inline ClsValue(std::string & s) : type(type_str) ,   dstr(s)  { data.data     = 0;   }
    inline ClsValue(const char * s)  : type(type_str) ,   dstr(s)  { data.data     = 0;   }
    inline ClsValue(char val)        : type(type_char),   dstr("") { data.ch       = val; }
    inline ClsValue(uint8_t val)     : type(type_uint8),  dstr("") { data.uint8    = val; }
    inline ClsValue(int8_t val)      : type(type_int8),   dstr("") { data.int8     = val; }
    inline ClsValue(uint16_t val)    : type(type_uint16), dstr("") { data.uint16   = val; }
    inline ClsValue(int16_t val)     : type(type_int16),  dstr("") { data.int16    = val; }
    inline ClsValue(uint32_t val)    : type(type_uint32), dstr("") { data.uint32   = val; }
    inline ClsValue(int32_t val)     : type(type_int32),  dstr("") { data.int32    = val; }
    inline ClsValue(uint64_t val)    : type(type_uint64), dstr("") { data.uint64   = val; }
    inline ClsValue(int64_t val)     : type(type_int64),  dstr("") { data.int64    = val; }
    inline ClsValue(float val)       : type(type_float),  dstr("") { data.v_float  = val; }
    inline ClsValue(double val)      : type(type_double), dstr("") { data.v_double = val; }

    inline ClsValue & operator = (ClsValue & src)   { type = src.type; data = src.data; dstr = src.dstr; return *this; }
    inline ClsValue & operator = (std::string & s)  { type = type_str;    dstr          = s;             return *this; }
    inline ClsValue & operator = (const char * s)   { type = type_str;    dstr          = s;             return *this; }
    inline ClsValue & operator = (uint8_t val)      { type = type_uint8;  data.uint8    = val;           return *this; }
    inline ClsValue & operator = (int8_t val)       { type = type_int8;   data.int8     = val;           return *this; }
    inline ClsValue & operator = (uint16_t val)     { type = type_uint16; data.uint16   = val;           return *this; }
    inline ClsValue & operator = (int16_t val)      { type = type_int16;  data.int16    = val;           return *this; }
    inline ClsValue & operator = (uint32_t val)     { type = type_uint32; data.uint32   = val;           return *this; }
    inline ClsValue & operator = (int32_t val)      { type = type_int32;  data.int32    = val;           return *this; }
    inline ClsValue & operator = (uint64_t val)     { type = type_uint64; data.uint64   = val;           return *this; }
    inline ClsValue & operator = (int64_t val)      { type = type_int64;  data.int64    = val;           return *this; }
    inline ClsValue & operator = (float val)        { type = type_float;  data.v_float  = val;           return *this; }
    inline ClsValue & operator = (double val)       { type = type_double; data.v_double = val;           return *this; }
    inline ClsValue & operator = (char val)         { type = type_char;   data.ch       = val;           return *this; }

    inline bool operator == (std::string & s)  const { return (dstr == s);              }
    inline bool operator == (const char * s)   const { return (dstr == s);              }
    inline bool operator == (uint8_t val)      const { return (val  == data.uint8    ); }
    inline bool operator == (int8_t val)       const { return (val  == data.int8     ); }
    inline bool operator == (uint16_t val)     const { return (val  == data.uint16   ); }
    inline bool operator == (int16_t val)      const { return (val  == data.int16    ); }
    inline bool operator == (uint32_t val)     const { return (val  == data.uint32   ); }
    inline bool operator == (int32_t val)      const { return (val  == data.int32    ); }
    inline bool operator == (uint64_t val)     const { return (val  == data.uint64   ); }
    inline bool operator == (int64_t val)      const { return (val  == data.int64    ); }
    inline bool operator == (float val)        const { return (val  == data.v_float  ); }
    inline bool operator == (double val)       const { return (val  == data.v_double ); }
    inline bool operator == (char val)         const { return (val  == data.ch       ); }
    inline bool operator == (ClsValue & src)   const;

    inline bool operator != (std::string & s)  const { return (dstr != s);              }
    inline bool operator != (const char * s)   const { return (dstr != s);              }
    inline bool operator != (uint8_t val)      const { return (val  != data.uint8    ); }
    inline bool operator != (int8_t val)       const { return (val  != data.int8     ); }
    inline bool operator != (uint16_t val)     const { return (val  != data.uint16   ); }
    inline bool operator != (int16_t val)      const { return (val  != data.int16    ); }
    inline bool operator != (uint32_t val)     const { return (val  != data.uint32   ); }
    inline bool operator != (int32_t val)      const { return (val  != data.int32    ); }
    inline bool operator != (uint64_t val)     const { return (val  != data.uint64   ); }
    inline bool operator != (int64_t val)      const { return (val  != data.int64    ); }
    inline bool operator != (float val)        const { return (val  != data.v_float  ); }
    inline bool operator != (double val)       const { return (val  != data.v_double ); }
    inline bool operator != (char val)         const { return (val  != data.ch       ); }
    inline bool operator != (ClsValue & src)   const;

    inline size_t           size(void)      const;
    inline ClsValue::Type_v get_type(void)  const   { return type; }
    inline ClsValue::vData  get(void)       const   { return data; }
    inline std::string      get_str(void)   const   { return dstr; }

    inline void * buff(void)                        { return static_cast<void*>(&(data.buff[0])); }
    inline size_t set_data(Type_v type, const uint8_t * buff, size_t size=0);
    inline size_t set_data_big(Type_v type, const uint8_t * buff, size_t size=0);

    inline size_t           get_data(    uint8_t * dst, size_t sz=0) const;
    inline size_t           get_data_big(uint8_t * dst, size_t sz=0) const;
    inline uint64_t         uint64(void)    const;
    inline int64_t          int64(void)     const;
    inline uint32_t         uint32(void)    const;
    inline int32_t          int32(void)     const;
    inline uint16_t         uint16(void)    const;
    inline int16_t          int16(void)     const;
    inline uint8_t          uint8(void)     const;
    inline int8_t           int8(void)      const;
    inline char             ch(void)        const;
    inline double           v_double(void)  const;
    inline float            v_float(void)   const;
    inline float            value(void)     const;
    inline std::string      str()
    {
        std::stringstream ss;
        switch(type)
        {
        case type_double:
            {   // effective 16 colmn
                char buff[512];
                size_t n;
                for(n=0; n < 15; n++)
                {
                    auto max = 10;
                    for(auto cnt=0; cnt<n; cnt++) max *= 10;
                    if(data.v_double < max) { break; }
                }
                char fmt[16];
                sprintf(fmt, "%%.%df", (16-n));
                sprintf(buff, fmt, data.v_double);
                dstr = buff;
            } break;
        case type_float:
            {   // effective 7 colomn
                char buff[512];
                size_t n;
                for(n=0; n < 6; n++)
                {
                    auto max = 10;
                    for(auto cnt=0; cnt<n; cnt++) max *= 10;
                    if(data.v_float < max) { break; }
                }
                char fmt[16];
                sprintf(fmt, "%%.%df", (7-n));
                sprintf(buff, fmt, data.v_float);
                dstr = buff;
            } break;
        case type_uint64:   ss << data.uint64;                   dstr = ss.str();  break;
        case type_int64:    ss << data.int64;                    dstr = ss.str();  break;
        case type_uint32:   ss << data.uint32;                   dstr = ss.str();  break;
        case type_int32:    ss << data.int32;                    dstr = ss.str();  break;
        case type_uint16:   ss << static_cast<int>(data.uint16); dstr = ss.str();  break;
        case type_int16:    ss << static_cast<int>(data.int16);  dstr = ss.str();  break;
        case type_uint8:    ss << static_cast<int>(data.uint8);  dstr = ss.str();  break;
        case type_int8:     ss << static_cast<int>(data.int8);   dstr = ss.str();  break;
        case type_char:     ss << static_cast<int>(data.int8);   dstr = ss.str();  break;
        case type_str:      return dstr; 
        case type_none:
        default:            return dstr;
        }
        return dstr;
    }
};
inline bool ClsValue::operator == (ClsValue & src)   const
{
    if(type != src.type) { return false; }
    switch(type)
    {
    case type_uint64:   return (data.uint64   == src.data.uint64  );
    case type_int64:    return (data.int64    == src.data.int64   );
    case type_double:   return (data.v_double == src.data.v_double);
    case type_uint32:   return (data.uint32   == src.data.uint32  );
    case type_int32:    return (data.int32    == src.data.int32   );
    case type_float:    return (data.v_float  == src.data.v_float );
    case type_uint16:   return (data.uint16   == src.data.uint16  );
    case type_int16:    return (data.int16    == src.data.int16   );
    case type_uint8:    return (data.uint8    == src.data.uint8   );
    case type_int8:     return (data.int8     == src.data.int8    );
    case type_char:     return (data.ch       == src.data.ch      );
    case type_str:      return (dstr          == src.dstr         );
    case type_none:
    default:            break;
    }
}
inline bool ClsValue::operator != (ClsValue & src)   const
{
    if(type != src.type) { return false; }
    switch(type)
    {
    case type_uint64:   return (data.uint64   != src.data.uint64  );
    case type_int64:    return (data.int64    != src.data.int64   );
    case type_double:   return (data.v_double != src.data.v_double);
    case type_uint32:   return (data.uint32   != src.data.uint32  );
    case type_int32:    return (data.int32    != src.data.int32   );
    case type_float:    return (data.v_float  != src.data.v_float );
    case type_uint16:   return (data.uint16   != src.data.uint16  );
    case type_int16:    return (data.int16    != src.data.int16   );
    case type_uint8:    return (data.uint8    != src.data.uint8   );
    case type_int8:     return (data.int8     != src.data.int8    );
    case type_char:     return (data.ch       != src.data.ch      );
    case type_str:      return (dstr          != src.dstr         );
    case type_none:
    default:            break;
    }
}
inline size_t ClsValue::size(void) const
{
    switch(type)
    {
    case type_uint64:   return sizeof(data.uint64);
    case type_int64:    return sizeof(data.int64);
    case type_double:   return sizeof(data.v_double);

    case type_uint32:   return sizeof(data.uint32);
    case type_int32:    return sizeof(data.int32);
    case type_float:    return sizeof(data.v_float);

    case type_uint16:   return sizeof(data.uint16);
    case type_int16:    return sizeof(data.int16);

    case type_uint8:    return sizeof(data.uint8);
    case type_int8:     return sizeof(data.int8);
    case type_char:     return sizeof(data.ch);

    case type_str:      return dstr.size();
    case type_none:
    default:            break;
    }
    return 0;
}
inline size_t ClsValue::set_data(Type_v type, const uint8_t * buff, size_t size)
{
    this->type = type;
    switch(type)
    {
    case type_uint64:   case type_int64:    case type_double:   size=8; std::memcpy(&(data.buff[0]), &(buff[0]), size); break;
    case type_uint32:   case type_int32:    case type_float:    size=4; std::memcpy(&(data.buff[0]), &(buff[0]), size); break;
    case type_uint16:   case type_int16:                        size=2; data.buff[0] = buff[0]; data.buff[1] = buff[1]; break;
    case type_uint8:    case type_int8:     case type_char:     size=1; data.buff[0] = buff[0];                         break;
    case type_str:
        {
            std::vector<char> buff_str(size+1);
            std::memcpy(&(buff_str[0]), &(buff[0]), size);
            buff_str[size] = '\0';
            dstr = &(buff_str[0]);
        }
        break;
    case type_none:
    default:
        break;
    }
    return size;
}
inline size_t ClsValue::set_data_big(Type_v type, const uint8_t * buff, size_t size)
{
    this->type = type;
    switch(type)
    {
    case type_uint64:   case type_int64:    case type_double: size=8; data.buff[0] = buff[7]; data.buff[1] = buff[6];
                                                                      data.buff[2] = buff[5]; data.buff[3] = buff[4];
                                                                      data.buff[4] = buff[3]; data.buff[5] = buff[2];
                                                                      data.buff[6] = buff[1]; data.buff[7] = buff[0]; break;
    case type_uint32:   case type_int32:    case type_float:  size=4; data.buff[0] = buff[3]; data.buff[1] = buff[2];
                                                                      data.buff[2] = buff[1]; data.buff[3] = buff[0]; break;
    case type_uint16:   case type_int16:                      size=2; data.buff[0] = buff[1]; data.buff[1] = buff[0]; break;
    case type_uint8:    case type_int8:     case type_char:   size=1; data.buff[0] = buff[0]; break;
    case type_str:
        {
            std::vector<char> buff_str(size+1);
            for(size_t idx = 0, top = size-1; idx < size; idx ++)
            {
                buff_str[idx] = buff[top - idx];
            };
            buff_str[size] = '\0';
            dstr = &(buff_str[0]);
        }
        break;
    case type_none:
    default:
        break;
    }
    return size;
}
inline size_t ClsValue::get_data(uint8_t * dst, size_t sz) const
{
    size_t len = size();
    sz = (sz == 0 ? len : (len < sz ? len : sz));
    if(type == type_str) { std::memcpy(dst, dstr.c_str(), sz); }
    else                 { std::memcpy(dst, data.buff,   sz); }
    return sz;
}
inline size_t ClsValue::get_data_big(uint8_t * dst, size_t sz) const
{
    size_t len = size();
    sz = (sz == 0 ? len : (len < sz ? len : sz));
    if(type != type_str) { const uint8_t * src = &(data.buff[0]); for(size_t idx=0, top=sz-1; idx<sz; idx++){ dst[top-idx] = src[idx]; } }
    else
    {
        const char * src = dstr.c_str();
        for(size_t idx = 0, top = sz-1; idx < sz; idx ++)
        {
            dst[top - idx] = src[idx];
        }
    }
    return sz;
}
inline uint64_t ClsValue::uint64(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<uint64_t>(data.uint64);
    case type_int64:    return static_cast<uint64_t>(data.int64);
    case type_uint32:   return static_cast<uint64_t>(data.uint32);
    case type_int32:    return static_cast<uint64_t>(data.int32);
    case type_uint16:   return static_cast<uint64_t>(data.uint16);
    case type_int16:    return static_cast<uint64_t>(data.int16);
    case type_uint8:    return static_cast<uint64_t>(data.uint8);
    case type_int8:     return static_cast<uint64_t>(data.int8);
    case type_char:     return static_cast<uint64_t>(data.ch);
    case type_double:   return static_cast<uint64_t>(data.v_double);
    case type_float:    return static_cast<uint64_t>(data.v_float);
    case type_str:      return static_cast<uint64_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline int64_t ClsValue::int64(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<int64_t>(data.uint64);
    case type_int64:    return static_cast<int64_t>(data.int64);
    case type_uint32:   return static_cast<int64_t>(data.uint32);
    case type_int32:    return static_cast<int64_t>(data.int32);
    case type_uint16:   return static_cast<int64_t>(data.uint16);
    case type_int16:    return static_cast<int64_t>(data.int16);
    case type_uint8:    return static_cast<int64_t>(data.uint8);
    case type_int8:     return static_cast<int64_t>(data.int8);
    case type_char:     return static_cast<int64_t>(data.ch);
    case type_double:   return static_cast<int64_t>(data.v_double);
    case type_float:    return static_cast<int64_t>(data.v_float);
    case type_str:      return static_cast<int64_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline uint32_t ClsValue::uint32(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<uint32_t>(data.uint64);
    case type_int64:    return static_cast<uint32_t>(data.int64);
    case type_uint32:   return static_cast<uint32_t>(data.uint32);
    case type_int32:    return static_cast<uint32_t>(data.int32);
    case type_uint16:   return static_cast<uint32_t>(data.uint16);
    case type_int16:    return static_cast<uint32_t>(data.int16);
    case type_uint8:    return static_cast<uint32_t>(data.uint8);
    case type_int8:     return static_cast<uint32_t>(data.int8);
    case type_char:     return static_cast<uint32_t>(data.ch);
    case type_double:   return static_cast<uint32_t>(data.v_double);
    case type_float:    return static_cast<uint32_t>(data.v_float);
    case type_str:      return static_cast<uint32_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline int32_t ClsValue::int32(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<int32_t>(data.uint64);
    case type_int64:    return static_cast<int32_t>(data.int64);
    case type_uint32:   return static_cast<int32_t>(data.uint32);
    case type_int32:    return static_cast<int32_t>(data.int32);
    case type_uint16:   return static_cast<int32_t>(data.uint16);
    case type_int16:    return static_cast<int32_t>(data.int16);
    case type_uint8:    return static_cast<int32_t>(data.uint8);
    case type_int8:     return static_cast<int32_t>(data.int8);
    case type_char:     return static_cast<int32_t>(data.ch);
    case type_double:   return static_cast<int32_t>(data.v_double);
    case type_float:    return static_cast<int32_t>(data.v_float);
    case type_str:      return static_cast<int32_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline uint16_t ClsValue::uint16(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<uint16_t>(data.uint64);
    case type_int64:    return static_cast<uint16_t>(data.int64);
    case type_uint32:   return static_cast<uint16_t>(data.uint32);
    case type_int32:    return static_cast<uint16_t>(data.int32);
    case type_uint16:   return static_cast<uint16_t>(data.uint16);
    case type_int16:    return static_cast<uint16_t>(data.int16);
    case type_uint8:    return static_cast<uint16_t>(data.uint8);
    case type_int8:     return static_cast<uint16_t>(data.int8);
    case type_char:     return static_cast<uint16_t>(data.ch);
    case type_double:   return static_cast<uint16_t>(data.v_double);
    case type_float:    return static_cast<uint16_t>(data.v_float);
    case type_str:      return static_cast<uint16_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline int16_t ClsValue::int16(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<int16_t>(data.uint64);
    case type_int64:    return static_cast<int16_t>(data.int64);
    case type_uint32:   return static_cast<int16_t>(data.uint32);
    case type_int32:    return static_cast<int16_t>(data.int32);
    case type_uint16:   return static_cast<int16_t>(data.uint16);
    case type_int16:    return static_cast<int16_t>(data.int16);
    case type_uint8:    return static_cast<int16_t>(data.uint8);
    case type_int8:     return static_cast<int16_t>(data.int8);
    case type_char:     return static_cast<int16_t>(data.ch);
    case type_double:   return static_cast<int16_t>(data.v_double);
    case type_float:    return static_cast<int16_t>(data.v_float);
    case type_str:      return static_cast<int16_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline uint8_t ClsValue::uint8(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<uint8_t>(data.uint64);
    case type_int64:    return static_cast<uint8_t>(data.int64);
    case type_uint32:   return static_cast<uint8_t>(data.uint32);
    case type_int32:    return static_cast<uint8_t>(data.int32);
    case type_uint16:   return static_cast<uint8_t>(data.uint16);
    case type_int16:    return static_cast<uint8_t>(data.int16);
    case type_uint8:    return static_cast<uint8_t>(data.uint8);
    case type_int8:     return static_cast<uint8_t>(data.int8);
    case type_char:     return static_cast<uint8_t>(data.ch);
    case type_double:   return static_cast<uint8_t>(data.v_double);
    case type_float:    return static_cast<uint8_t>(data.v_float);
    case type_str:      return static_cast<uint8_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline int8_t ClsValue::int8(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<int8_t>(data.uint64);
    case type_int64:    return static_cast<int8_t>(data.int64);
    case type_uint32:   return static_cast<int8_t>(data.uint32);
    case type_int32:    return static_cast<int8_t>(data.int32);
    case type_uint16:   return static_cast<int8_t>(data.uint16);
    case type_int16:    return static_cast<int8_t>(data.int16);
    case type_uint8:    return static_cast<int8_t>(data.uint8);
    case type_int8:     return static_cast<int8_t>(data.int8);
    case type_char:     return static_cast<int8_t>(data.ch);
    case type_double:   return static_cast<int8_t>(data.v_double);
    case type_float:    return static_cast<int8_t>(data.v_float);
    case type_str:      return static_cast<int8_t>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline char ClsValue::ch(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<char>(data.uint64);
    case type_int64:    return static_cast<char>(data.int64);
    case type_uint32:   return static_cast<char>(data.uint32);
    case type_int32:    return static_cast<char>(data.int32);
    case type_uint16:   return static_cast<char>(data.uint16);
    case type_int16:    return static_cast<char>(data.int16);
    case type_uint8:    return static_cast<char>(data.uint8);
    case type_int8:     return static_cast<char>(data.int8);
    case type_char:     return static_cast<char>(data.ch);
    case type_double:   return static_cast<char>(data.v_double);
    case type_float:    return static_cast<char>(data.v_float);
    case type_str:      return static_cast<char>(stoi(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline double ClsValue::v_double(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<double>(data.uint64);
    case type_int64:    return static_cast<double>(data.int64);
    case type_uint32:   return static_cast<double>(data.uint32);
    case type_int32:    return static_cast<double>(data.int32);
    case type_uint16:   return static_cast<double>(data.uint16);
    case type_int16:    return static_cast<double>(data.int16);
    case type_uint8:    return static_cast<double>(data.uint8);
    case type_int8:     return static_cast<double>(data.int8);
    case type_char:     return static_cast<double>(data.ch);
    case type_double:   return static_cast<double>(data.v_double);
    case type_float:    return static_cast<double>(data.v_float);
    case type_str:      return static_cast<double>(stod(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline float ClsValue::v_float(void) const
{
    switch(type)
    {
    case type_uint64:   return static_cast<float>(data.uint64);
    case type_int64:    return static_cast<float>(data.int64);
    case type_uint32:   return static_cast<float>(data.uint32);
    case type_int32:    return static_cast<float>(data.int32);
    case type_uint16:   return static_cast<float>(data.uint16);
    case type_int16:    return static_cast<float>(data.int16);
    case type_uint8:    return static_cast<float>(data.uint8);
    case type_int8:     return static_cast<float>(data.int8);
    case type_char:     return static_cast<float>(data.ch);
    case type_double:   return static_cast<float>(data.v_double);
    case type_float:    return static_cast<float>(data.v_float);
    case type_str:      return static_cast<float>(stof(dstr));
    case type_none:
    default:
        break;
    }
    return 0;
}
inline float ClsValue::value(void) const { return v_float(); }

/**
 * Regexp for c++
 *
 */
class CppRegexp
{
public:
    struct MatchPosition { size_t pos; size_t len; };
private:
    std::vector<std::regex> regs;
public:
    inline CppRegexp(void)                              : regs(0) { }
    inline CppRegexp(std::string & str)                 : regs(1) { std::regex reg(str);                       regs[0] = reg; }
    inline CppRegexp(const char * arg)                  : regs(1) { std::string str(arg); std::regex reg(str); regs[0] = reg; }
    inline CppRegexp(const std::list<std::string> arg)  : regs(arg.size()) { size_t idx = 0; for(auto & str : arg) { std::regex reg(str); regs[idx] = reg; idx ++; } }
    virtual ~CppRegexp(void)                                { }

    inline void reg_add(const std::string & str)            { std::regex reg(str); regs.push_back(reg); }
    inline void reg_add(const std::list<std::string> & arg) { for(auto & str : arg) { reg_add(str); } }
    inline unsigned int length(void)                        { return regs.size(); }

    inline bool match(const std::string & str);
    inline std::list<std::string> match(std::list<std::string> & text);
    inline std::list<std::string> grep(std::list<std::string> & text);
    inline std::string replace(const char * str, size_t idx, const char * rep);
    inline std::string replace(const std::string & str, size_t idx, const char * rep);
    inline void replace(std::list<std::string> & text, size_t idx, const char * rep);
    inline void replace(std::list<std::string> & text, const char * rep);
    inline unsigned int select(const char * str);
    inline unsigned int select(const std::string & str);
    inline std::list<std::string> split(const std::string & src);
    inline std::list<CppRegexp::MatchPosition> matches(std::string & str);
};

inline bool CppRegexp::match(const std::string & str)
{
    for(auto & reg : regs)
    {
        if(std::regex_search(str, reg)){ return true; }
    }
    return false;
}

inline std::list<std::string> CppRegexp::match(std::list<std::string> & text)
{
    std::list<std::string> result;
    for(auto & str : text)
    {
        if(match(str)) { result.push_back(str); }
    }
    return result;
}

inline std::list<std::string> CppRegexp::grep(std::list<std::string> & text)
{
    std::list<std::string> result;
    if(0 < regs.size())
    {
        for(auto & str : text)
        {
            bool match = true;
            for(auto & reg : regs)
            {
                if(!std::regex_search(str, reg))
                {
                    match = false;
                    break;
                }
            }
            if(match)
            {
                result.push_back(str);
            }
        }
    }
    return result;
}

inline std::string CppRegexp::replace(const char * str, size_t idx, const char * rep)
{
    if((idx<regs.size())&&(nullptr!=rep)&&(nullptr!=str))
    {
        return std::regex_replace(str, regs[idx], rep);
    }
    return std::string(str);
}

inline std::string CppRegexp::replace(const std::string & str, size_t idx, const char * rep)
{
    if((idx<regs.size())&&(nullptr!=rep))
    {
        return std::regex_replace(str, regs[idx], rep);
    }
    return str;
}

inline void CppRegexp::replace(std::list<std::string> & text, size_t idx, const char * rep)
{
    if((idx<regs.size())&&(nullptr!=rep))
    {
        for(auto & str : text)
        {
            str = std::regex_replace(str, regs[idx], rep);
        }
    }
}

inline void CppRegexp::replace(std::list<std::string> & text, const char * rep)
{
    if( rep != nullptr )
    {
        for(auto & str : text)
        {
            for(auto & reg : regs)
            {
                str = std::regex_replace(str, reg, rep);
            }
        }
    }
}

inline unsigned int CppRegexp::select(const char * str)
{
    if(0 < regs.size())
    {
        unsigned int idx = 0;
        for(auto & reg : regs)
        {
            if( std::regex_search(str, reg) )
            {
                break;
            }
            idx ++;
        }
        return idx;
    }
    return 1;
}

inline unsigned int CppRegexp::select(const std::string & str)
{
    return select(str.c_str());
}

inline std::list<std::string> CppRegexp::split(const std::string & src)
{
    auto str_split = [](std::string & src, std::regex & reg)
    {
        std::list<std::string> result;
        std::copy( std::sregex_token_iterator{src.begin(), src.end(), reg, -1}, std::sregex_token_iterator{}, std::back_inserter(result) );
        return result;
    };
    std::list<std::string> result;
    result.push_back(src);
    for(auto & reg : regs)
    {
        std::list<std::string> temp;
        for(auto str : result)
        {
            for(auto & item : str_split(str, reg))
            {
                temp.push_back(item);
            }
        }
        result.clear();
        result = temp;
    }
    return result;
}

inline std::list<CppRegexp::MatchPosition> CppRegexp::matches(std::string & str)
{
    std::list<CppRegexp::MatchPosition> list;
    std::smatch m;
    std::string::const_iterator searchStart(str.cbegin());
    size_t pos=0;
    while(std::regex_search(searchStart, str.cend(), m, regs[0]))
    {
        CppRegexp::MatchPosition match;
        pos += m.position(0);
        match.pos = pos;
        match.len = m.length(0);
        pos += match.len;
        list.push_back(match);
        searchStart = m.suffix().first;
    }
    return list;
}

/**
 * Binary Data Edit Class
 *
 */
class BinaryControl
{
protected:
    size_t                  pos;
    std::vector<uint8_t>    bin;

public:
    inline unsigned char toValue(unsigned char data)
    {
        unsigned char val=0xff;
             if(('0' <= data) && (data<='9')) { val = data - '0';      }
        else if(('a' <= data) && (data<='f')) { val = 10 + data - 'a'; }
        else if(('A' <= data) && (data<='F')) { val = 10 + data - 'A'; }
        else                                  { }
        return val;
    }

public:
    inline BinaryControl(void) : pos(0), bin(0) { }
    inline BinaryControl(BinaryControl & src);
    inline BinaryControl(size_t len) : pos(0), bin(len) { }
    inline BinaryControl(size_t len, uint8_t val);
    inline BinaryControl(const uint8_t * src, size_t size);
    inline BinaryControl(std::string & data);
    inline BinaryControl(std::list<BinaryControl *> & list);
    inline BinaryControl(std::list<ClsValue> arry);
    virtual ~BinaryControl(void) { }

    inline size_t           size(void)         const    { return bin.size(); }
    inline uint8_t *        data(size_t idx=0)          { return &(bin[idx]); }
    inline const uint8_t *  data(size_t idx=0) const    { return &(bin[idx]); }
    inline char *           ptr(size_t  idx=0)          { return reinterpret_cast<char *>(      &(bin[idx])); }
    inline const char *     ptr(size_t  idx=0) const    { return reinterpret_cast<const char *>(&(bin[idx])); }

    inline size_t &         ref_pos(void)               { return pos; }
    inline size_t           get_pos(void)      const    { return pos; }
    inline void             set_pos(size_t pos=0)       { if(pos <= size()){this->pos = pos; } }

    inline size_t           resize(size_t size)         { pos = (pos <= size) ? pos : 0; bin.resize(size); return bin.size(); }

    inline void clone(const BinaryControl & src);
    inline void clone(const BinaryControl & src, size_t size);
    inline void clone(const BinaryControl & src, size_t address, size_t size);
    inline void swap(BinaryControl & src)               { size_t temp = pos; pos = src.pos; src.pos = temp; bin.swap(src.bin); }

    inline size_t memset(size_t address, uint8_t val, size_t sz);
    inline size_t fill(uint8_t val, size_t len);
    inline size_t fill(uint8_t val=0);

    inline size_t get_data(uint8_t * dst, size_t len, size_t begin=0) const;

    inline size_t memcpy(size_t address_dst, const uint8_t * src, size_t len);
    inline size_t memcpy(const uint8_t * src, size_t len);
    inline size_t memcpy(size_t address_dst, size_t address_src, BinaryControl & src, size_t len);
    inline size_t memcpy(BinaryControl & src, size_t len);
    inline size_t memcpy(BinaryControl & src);
    inline BinaryControl & operator += (BinaryControl & src);
    inline uint8_t operator [] (size_t idx) const { return (idx<bin.size() ? bin[idx]: 0); };

    inline int memcmp(size_t address_dst, size_t address_src, const BinaryControl & src, size_t len)    const;
    inline int memcmp(BinaryControl & src, size_t len)                                                  const;
    inline int memcmp(BinaryControl & src)                                                              const;

    inline size_t write(std::string & src, size_t size, size_t address=0);
    inline size_t write_big(std::string & src, size_t size, size_t address=0);

    inline size_t dump(std::string & output, size_t address, size_t size) const;
    inline size_t dump(std::string & output, size_t address=0) const;
    inline std::string dump(void) const;
    inline size_t dump_big(std::string & output, size_t address, size_t size) const;
    inline size_t dump_big(std::string & output, size_t address=0) const;
    inline std::string dump_big(void) const;

    inline size_t get(std::list<ClsValue> & list, const std::string & fmt, uint32_t address=0) const;
    inline std::vector<ClsValue> get(const std::string & fmt);
    inline size_t set(std::list<ClsValue> & arry, size_t address);
    inline size_t set(std::list<ClsValue> & arry);

    inline void loadBinaryFile(std::string & fname);
    inline void saveBinaryFile(std::string & fname);

    inline std::list<size_t> toAddressList(std::string & addr) const;
};
inline size_t BinaryControl::memset(size_t address, uint8_t val, size_t sz)
{
    size_t len = 0;
    if(address < size())
    {
        len = size() - address;
        if(sz < len){ len = sz; }
        std::memset(data(address), val, len);
    }
    return len;
}
inline size_t BinaryControl::fill(uint8_t val, size_t len)  { return memset(0, val, len);      }
inline size_t BinaryControl::fill(uint8_t val)              { return memset(0, val, size());   }
inline size_t BinaryControl::get_data(uint8_t * dst, size_t len, size_t begin) const
{
    len = (len < size() ? len : size());
    std::memcpy(dst, data(begin), len);
    return len;
}
inline size_t BinaryControl::memcpy(size_t address_dst, const uint8_t * src, size_t len)
{
    if(size() < (address_dst+len)) { resize(address_dst+len); }
    std::memcpy(data(address_dst), src, len);
    return len;
}
inline size_t BinaryControl::memcpy(const uint8_t * src, size_t len) { return memcpy(0, src, len); }
inline size_t BinaryControl::memcpy(size_t address_dst, size_t address_src, BinaryControl & src, size_t len)
{
    auto dst_len = size()     - address_dst;
    auto src_len = src.size() - address_src;
    if(dst_len < len) { len = dst_len; }
    if(src_len < len) { len = src_len; }
    if(0 < len)
    {
        std::memcpy(data(address_dst), src.data(address_src), len);
    }
    return len;
}
inline size_t BinaryControl::memcpy(BinaryControl & src, size_t len)    { return memcpy(0, 0, src, len); }
inline size_t BinaryControl::memcpy(BinaryControl & src)                { return memcpy(0, 0, src, (size()<src.size()?size():src.size())); }
inline BinaryControl & BinaryControl::operator += (BinaryControl & src) { resize(size() + src.size()); memcpy(size(), src.data(), src.size()); return *this; }
inline int BinaryControl::memcmp(size_t address_dst, size_t address_src, const BinaryControl & src, size_t len) const
{
    auto dst_len = size()     - address_dst;
    auto src_len = src.size() - address_src;
    if(dst_len < len) { len = dst_len; }
    if(src_len < len) { len = src_len; }
    if(0 < len)       { return std::memcmp(data(address_dst), src.data(address_src), len); }
    return -2;
}
inline int BinaryControl::memcmp(BinaryControl & src, size_t len)   const { return memcmp(0, 0, src, len); }
inline int BinaryControl::memcmp(BinaryControl & src)               const { return memcmp(src, (size()<src.size()?size():src.size())); }
inline size_t BinaryControl::write(std::string & src, size_t size, size_t address)
{
    auto wlen = 0;
    std::vector<uint8_t> bin(src.size()/2);
    const uint8_t * str = reinterpret_cast<const unsigned char *>(src.c_str());
    uint8_t tmp = 0xff;
    for(auto idx=0; idx<src.size(); idx++)
    {
        if(0xff == tmp) { tmp = toValue(str[idx]); }
        else
        {
            auto v = toValue(str[idx]);
            if(0xff != v)
            {
                tmp = (tmp << 4) | v;
                bin[wlen++] = tmp;
                tmp = 0xff;
            }
        }
    }
    if(0 == size)        { size = wlen; }
    else if(wlen < size) { size = wlen; }
    else { }
    if(this->size() < (address+size)) { resize(address+size); }
    memcpy(address, &(bin[0]), size);
    return size;
}
inline size_t BinaryControl::write_big(std::string & src, size_t size, size_t address)
{
    auto wlen = 0;
    std::vector<uint8_t> bin(src.size()/2);
    const uint8_t * str = reinterpret_cast<const unsigned char *>(src.c_str());
    uint8_t tmp = 0xff;
    for(auto idx=0; idx<src.size(); idx++)
    {
        if(0xff == tmp) { tmp = toValue(str[idx]); }
        else
        {
            auto v = toValue(str[idx]);
            if(0xff != v)
            {
                tmp = (tmp << 4) | v;
                bin[wlen++] = tmp;
                tmp = 0xff;
            }
        }
    }
    if(0 == size)        { size = wlen; }
    else if(wlen < size) { size = wlen; }
    else { }
    if(this->size() < (address+size)) { this->resize(address+size); }
    uint8_t * data = this->data();
    for(size_t idx = 0, top = size - 1; idx < size; idx ++){ data[address + (top - idx)] = bin[idx]; }
    return size;
}
inline size_t BinaryControl::dump(std::string & output, size_t address, size_t size) const
{
    auto len = this->size();
    if(address < len)
    {
        len -= address;
        if(size < len) { len = size; }
        if(0 < len)
        {
            for(size_t idx=0; idx<len; idx++)
            {
                char temp[4] = { 0 };
                sprintf(temp, "%02X", bin[address+idx]);
                output += temp;
            }
        }
    }
    return len;
}
inline size_t BinaryControl::dump(std::string & output, size_t address) const
{
    return dump(output, address, bin.size());
}
inline std::string BinaryControl::dump(void) const
{
    std::string output;
    dump(output);
    return output;
}
inline size_t BinaryControl::dump_big(std::string & output, size_t address, size_t size) const
{
    auto len = this->size();
    if(address < len)
    {
        len -= address;
        if(size < len) { len = size; }
        if(0 < len)
        {
            for(size_t idx=0, top=len-1; idx<len; idx++)
            {
                char temp[4] = { 0 };
                sprintf(temp, "%02X", bin[address + (top - idx)]);
                output += temp;
            }
        }
    }
    return len;
}
inline size_t BinaryControl::dump_big(std::string & output, size_t address) const
{
    return dump_big(output, address, bin.size());
}
inline std::string BinaryControl::dump_big(void) const
{
    std::string output;
    dump_big(output);
    return output;
}
inline size_t BinaryControl::get(std::list<ClsValue> & list, const std::string & fmt, uint32_t address) const
{
    char state = ' ';
    std::string num;
    auto format = fmt + ' ';
    auto act_c = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_int8,       data(address)); list.push_back(temp); };
    auto act_b = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_uint8,      data(address)); list.push_back(temp); };
    auto act_s = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_int16,      data(address)); list.push_back(temp); };
    auto act_w = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_uint16,     data(address)); list.push_back(temp); };
    auto act_i = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_int32,      data(address)); list.push_back(temp); };
    auto act_d = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_uint32,     data(address)); list.push_back(temp); };
    auto act_j = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_int64,      data(address)); list.push_back(temp); };
    auto act_q = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_uint64,     data(address)); list.push_back(temp); };
    auto act_f = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_float,      data(address)); list.push_back(temp); };
    auto act_v = [&]() { ClsValue temp; address +=temp.set_data(ClsValue::type_double,     data(address)); list.push_back(temp); };
    auto act_S = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_int16,  data(address)); list.push_back(temp); };
    auto act_W = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_uint16, data(address)); list.push_back(temp); };
    auto act_I = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_int32,  data(address)); list.push_back(temp); };
    auto act_D = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_uint32, data(address)); list.push_back(temp); };
    auto act_J = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_int64,  data(address)); list.push_back(temp); };
    auto act_Q = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_uint64, data(address)); list.push_back(temp); };
    auto act_F = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_float,  data(address)); list.push_back(temp); };
    auto act_V = [&]() { ClsValue temp; address +=temp.set_data_big(ClsValue::type_double, data(address)); list.push_back(temp); };
    std::map<char, std::function<void()>> act = {  {'c', act_c}, {'b', act_b}, {'s', act_s}, {'w', act_w}, {'i', act_i}, {'d', act_d}, {'j', act_j}, {'q', act_q}, {'f', act_f}, {'v', act_v},
                                                                               {'S', act_S}, {'W', act_W}, {'I', act_I}, {'D', act_D}, {'J', act_J}, {'Q', act_Q}, {'F', act_F}, {'V', act_V} };
    auto act_a = [&]() { size_t len=stoi(num); len = (len <= (size()-address) ? len : size()-address); ClsValue temp; address += temp.set_data(    ClsValue::type_str, data(address), len); list.push_back(temp); };
    auto act_A = [&]() { size_t len=stoi(num); len = (len <= (size()-address) ? len : size()-address); ClsValue temp; address += temp.set_data_big(ClsValue::type_str, data(address), len); list.push_back(temp); };
    auto act_h = [&]() { std::string hex; address += dump(    hex, address, stoi(num)); ClsValue temp(hex); list.push_back(temp); };
    auto act_H = [&]() { std::string hex; address += dump_big(hex, address, stoi(num)); ClsValue temp(hex); list.push_back(temp); };
    std::map<char, std::function<void()>> act2 = { {'a', act_a}, {'A', act_A}, {'h', act_h}, {'H', act_H} };
    for(auto ch: format)
    {
        if(('0' <= ch) && (ch <= '9')) { num += ch; }
        else
        {
            if(0 < act2.count(state)) { (act2[state])(); }
            num.clear();
            if(0 < act.count(ch)) { (act[ch])(); }
            state = ch;
        }
    }
    return address;
}
inline std::vector<ClsValue> BinaryControl::get(const std::string & fmt)
{
    std::list<ClsValue> list;
    pos = get(list, fmt, pos);
    std::vector<ClsValue> arry(list.begin(), list.end());
    return arry;
}
inline size_t BinaryControl::set(std::list<ClsValue> & arry, size_t address)
{
    size_t len = 0;
    for(auto & val : arry)
    {
        auto sz = val.get_data(data(address), size()-address);
        len += sz;
        address += sz;
        if(size() <= address) break;
    }
    return len;
}
inline size_t BinaryControl::set(std::list<ClsValue> & arry)
{
    auto len = set(arry, pos);
    pos += len;
    return pos;
}
inline void BinaryControl::loadBinaryFile(std::string & fname)
{
    std::filesystem::path path(fname);
    if(std::filesystem::exists(fname))
    {
        resize(std::filesystem::file_size(path));
        if(0 < size())
        {
            std::ifstream fin(fname, std::ios::binary);
            if(fin.is_open()) { fin.read(ptr(), size()); }
            else              { resize(0); }
        }
    }
}
inline void BinaryControl::saveBinaryFile(std::string & fname)
{
    std::ofstream fout(fname, std::ios::binary);
    fout.write(reinterpret_cast<char *>(ptr()), size());
}
inline void BinaryControl::clone(const BinaryControl & src, size_t address, size_t size)
{
    size=(size<=src.size()? size: src.size());
    resize(size);
    std::memcpy(data(), src.data(), size);
}
inline void BinaryControl::clone(const BinaryControl & src, size_t size)                    { clone(src, 0, size);       }
inline void BinaryControl::clone(const BinaryControl & src)                                 { clone(src, 0, src.size()); }
inline BinaryControl::BinaryControl(BinaryControl & src)                : pos(0), bin(0)    { clone(src, 0, src.size());     }
inline BinaryControl::BinaryControl(size_t len, uint8_t val)            : pos(0), bin(len)  { std::memset(data(), val, len); }
inline BinaryControl::BinaryControl(const uint8_t * src, size_t len)    : pos(0), bin(len)  { std::memcpy(data(), src, len); }
inline BinaryControl::BinaryControl(std::string & data)                 : pos(0), bin(0)
{
    CppRegexp reg({"^file:", "^tx:"});
    switch(reg.select(data))
    {
    case 0: /* file      */ { auto fname = reg.replace(data, 0, ""); loadBinaryFile(fname);                                     } break;
    case 1: /* text data */ { data = reg.replace(data, 1, ""); memcpy(reinterpret_cast<const uint8_t *>(data.c_str()), size()); } break;
    default:                { write(data, size());                                                                              } break;
    }
}
inline BinaryControl::BinaryControl(std::list<BinaryControl *> & list_bin)
  : pos(0), bin(0)
{
    for(auto & bin : list_bin){ *this += *bin; }
}
inline BinaryControl::BinaryControl(std::list<ClsValue> arry)
  : pos(0), bin(0)
{
    size_t len = 0;
    for(auto & v: arry){ len += v.size(); }
    resize(len);
    set(arry, 0);
}
inline std::list<size_t> BinaryControl::toAddressList(std::string & addr) const
{
    uint16_t v_temp = 0;
    std::list<uint16_t> list_bit;
    uint8_t state = 0, last = 0;
    size_t cnt = 0;
    auto act_0   = [&]() { v_temp = 0x0001; list_bit.push_back(v_temp); };
    auto act_1   = [&]() { v_temp = 0x0002; list_bit.push_back(v_temp); };
    auto act_2   = [&]() { v_temp = 0x0004; list_bit.push_back(v_temp); };
    auto act_3   = [&]() { v_temp = 0x0008; list_bit.push_back(v_temp); };
    auto act_4   = [&]() { v_temp = 0x0010; list_bit.push_back(v_temp); };
    auto act_5   = [&]() { v_temp = 0x0020; list_bit.push_back(v_temp); };
    auto act_6   = [&]() { v_temp = 0x0040; list_bit.push_back(v_temp); };
    auto act_7   = [&]() { v_temp = 0x0080; list_bit.push_back(v_temp); };
    auto act_8   = [&]() { v_temp = 0x0100; list_bit.push_back(v_temp); };
    auto act_9   = [&]() { v_temp = 0x0200; list_bit.push_back(v_temp); };
    auto act_A   = [&]() { v_temp = 0x0400; list_bit.push_back(v_temp); };
    auto act_B   = [&]() { v_temp = 0x0800; list_bit.push_back(v_temp); };
    auto act_C   = [&]() { v_temp = 0x1000; list_bit.push_back(v_temp); };
    auto act_D   = [&]() { v_temp = 0x2000; list_bit.push_back(v_temp); };
    auto act_E   = [&]() { v_temp = 0x4000; list_bit.push_back(v_temp); };
    auto act_F   = [&]() { v_temp = 0x8000; list_bit.push_back(v_temp); };
    auto act_dot = [&]() { v_temp = 0xffff; list_bit.push_back(v_temp); };
    auto act_mul = [&]() { v_temp = 0; state = 1; };
    auto act_cnt = [&]() { state = 2; cnt = 0; };
    std::map<char, std::function<void()>> act =
    {
        {'0', act_0}, {'1', act_1}, {'2', act_2}, {'3', act_3}, {'4', act_4}, {'5', act_5}, {'6', act_6}, {'7', act_7}, {'8', act_8}, {'9', act_9},
        {'A', act_A}, {'B', act_B}, {'C', act_C}, {'D', act_D}, {'E', act_E}, {'F', act_F},
        {'a', act_A}, {'b', act_B}, {'c', act_C}, {'d', act_D}, {'e', act_E}, {'f', act_F},
        {'.', act_dot}, {'[', act_mul}, {'{', act_cnt}
    };

    auto act1_0   = [&]() { v_temp |= 0x0001;  last =  0; };
    auto act1_1   = [&]() { v_temp |= 0x0002; if(0x80&last) { for(auto n=last&0x0f; n< 1; n++) { v_temp |= (0x0001<<n); } }; last =  1; };
    auto act1_2   = [&]() { v_temp |= 0x0004; if(0x80&last) { for(auto n=last&0x0f; n< 2; n++) { v_temp |= (0x0001<<n); } }; last =  2; };
    auto act1_3   = [&]() { v_temp |= 0x0008; if(0x80&last) { for(auto n=last&0x0f; n< 3; n++) { v_temp |= (0x0001<<n); } }; last =  3; };
    auto act1_4   = [&]() { v_temp |= 0x0010; if(0x80&last) { for(auto n=last&0x0f; n< 4; n++) { v_temp |= (0x0001<<n); } }; last =  4; };
    auto act1_5   = [&]() { v_temp |= 0x0020; if(0x80&last) { for(auto n=last&0x0f; n< 5; n++) { v_temp |= (0x0001<<n); } }; last =  5; };
    auto act1_6   = [&]() { v_temp |= 0x0040; if(0x80&last) { for(auto n=last&0x0f; n< 6; n++) { v_temp |= (0x0001<<n); } }; last =  6; };
    auto act1_7   = [&]() { v_temp |= 0x0080; if(0x80&last) { for(auto n=last&0x0f; n< 7; n++) { v_temp |= (0x0001<<n); } }; last =  7; };
    auto act1_8   = [&]() { v_temp |= 0x0100; if(0x80&last) { for(auto n=last&0x0f; n< 8; n++) { v_temp |= (0x0001<<n); } }; last =  8; };
    auto act1_9   = [&]() { v_temp |= 0x0200; if(0x80&last) { for(auto n=last&0x0f; n< 9; n++) { v_temp |= (0x0001<<n); } }; last =  9; };
    auto act1_A   = [&]() { v_temp |= 0x0400; if(0x80&last) { for(auto n=last&0x0f; n<10; n++) { v_temp |= (0x0001<<n); } }; last = 10; };
    auto act1_B   = [&]() { v_temp |= 0x0800; if(0x80&last) { for(auto n=last&0x0f; n<11; n++) { v_temp |= (0x0001<<n); } }; last = 11; };
    auto act1_C   = [&]() { v_temp |= 0x1000; if(0x80&last) { for(auto n=last&0x0f; n<12; n++) { v_temp |= (0x0001<<n); } }; last = 12; };
    auto act1_D   = [&]() { v_temp |= 0x2000; if(0x80&last) { for(auto n=last&0x0f; n<13; n++) { v_temp |= (0x0001<<n); } }; last = 13; };
    auto act1_E   = [&]() { v_temp |= 0x4000; if(0x80&last) { for(auto n=last&0x0f; n<14; n++) { v_temp |= (0x0001<<n); } }; last = 14; };
    auto act1_F   = [&]() { v_temp |= 0x8000; if(0x80&last) { for(auto n=last&0x0f; n<15; n++) { v_temp |= (0x0001<<n); } }; last = 15; };
    auto act1_huf = [&]() { last |= 0x80; };
    auto act1_end = [&]() { list_bit.push_back(v_temp); state = 0; };
    std::map<char, std::function<void()>> act1 =
    {
        {'0', act1_0}, {'1', act1_1}, {'2', act1_2}, {'3', act1_3}, {'4', act1_4}, {'5', act1_5}, {'6', act1_6}, {'7', act1_7}, {'8', act1_8}, {'9', act1_9},
        {'A', act1_A}, {'B', act1_B}, {'C', act1_C}, {'D', act1_D}, {'E', act1_E}, {'F', act1_F},
        {'a', act1_A}, {'b', act1_B}, {'c', act1_C}, {'d', act1_D}, {'e', act1_E}, {'f', act1_F},
        {'-', act1_huf}, {']', act1_end},
    };

    auto act2_0   = [&]() { cnt = (cnt * 10) + 0; };
    auto act2_1   = [&]() { cnt = (cnt * 10) + 1; };
    auto act2_2   = [&]() { cnt = (cnt * 10) + 2; };
    auto act2_3   = [&]() { cnt = (cnt * 10) + 3; };
    auto act2_4   = [&]() { cnt = (cnt * 10) + 4; };
    auto act2_5   = [&]() { cnt = (cnt * 10) + 5; };
    auto act2_6   = [&]() { cnt = (cnt * 10) + 6; };
    auto act2_7   = [&]() { cnt = (cnt * 10) + 7; };
    auto act2_8   = [&]() { cnt = (cnt * 10) + 8; };
    auto act2_9   = [&]() { cnt = (cnt * 10) + 9; };
    auto act2_end = [&]() { for(size_t n=1; n<cnt; n++) { list_bit.push_back(v_temp); }; state = 0; };
    std::map<char, std::function<void()>> act2 = { {'0', act2_0}, {'1', act2_1}, {'2', act2_2}, {'3', act2_3}, {'4', act2_4}, {'5', act2_5}, {'6', act2_6}, {'7', act2_7}, {'8', act2_8}, {'9', act2_9}, {'}', act2_end} };

    auto state_0 = [&](char & ch) { if(0 < act.count(ch))  { (act[ch])(); } };
    auto state_1 = [&](char & ch) { if(0 < act1.count(ch)) { (act1[ch])(); } };
    auto state_2 = [&](char & ch) { if(0 < act2.count(ch)) { (act2[ch])(); } };
    std::vector<std::function<void(char & ch)>> act_state = { state_0, state_1, state_2 };
    for(auto & ch : addr)
    {
        if(state < act_state.size()) { (act_state[state])(ch); }
        else                         { break; }
    }
    std::list<size_t> list_addr({0});
    for(auto bit : list_bit)
    {
        std::list<uint16_t> vlist;
        for(auto n = 0; (n < 16) && (0!=bit); n ++)
        {
            uint16_t mask = 0x0001 << n;
            if(bit & mask) { vlist.push_back(n);  bit &= ~mask; } }
        std::list<size_t> temp;
        for(auto & addr : list_addr) { for(auto v : vlist) { temp.push_back((addr*16)+v); } }
        list_addr.swap(temp);
    }
    return list_addr;
}


#endif
