/**
 * utilities file of C language
 *
 * @file MyUtilities.h
 * @brief C utilitis library
 * @author Shouji, Igarashi
 *
 * (c) 2018 Shouji, Igarashi.
 */

#ifndef __MyUtilities_h__
#define __MyUtilities_h__

#include <stdlib.h>

/* 16/32 bit Architecture */
/* unsigned char  :  8 bit */
/* unsigned short : 16 bit */
/* unsigned long  : 32 bit */
/* float          : 32 bit */
/* unsigned int   : 16/32 bit */

union Byte
{
    unsigned char   data;
    signed char     val;
    unsigned char   buff[1];
};

union Word
{
    unsigned short  data;
    signed short    val;
    unsigned char   buff[2];
    union Byte      byte;
    union Byte      bytes[2];
};

union DWord
{
#if __x86_64__
    unsigned int    data;
    signed int      val;
#else
    unsigned long   data;
    signed long     val;
#endif
    float           value;
    unsigned char   buff[4];
    union Byte      byte;
    union Word      word;
    union Byte      bytes[4];
    union Word      words[2];
};

struct Range
{
    size_t idx;
    size_t cnt;
};

struct RecordInfomation
{
    unsigned int DWordCount;
    unsigned int WordCount;
    unsigned int ByteCount;
    unsigned int RecCount;
    const unsigned short * const * rec_ids;
    const unsigned short *         rec_size;
};

#ifdef __cplusplus
extern "C"
{
#endif
size_t getIndexArrayByte(const unsigned char * array, size_t count, const unsigned char target);
size_t getIndexArrayWord(const unsigned short * array, size_t count, const unsigned short target);
size_t getIndexArrayDWord(const unsigned long * array, size_t count, const unsigned long target);
size_t getIndexArrayCString(const char * array[], size_t count, const char * target);
struct Range getRangeOfListByte(const unsigned char * const list[], const unsigned char list_sz[], const size_t count, const size_t pos, const unsigned char target);

unsigned char getBitIndex8(unsigned char target);
unsigned char getBitIndex16(unsigned short target);
unsigned char getBitIndex32(union DWord target);

unsigned char copyBitByte(const unsigned short * chkBit, const unsigned char * resultBit, size_t size, unsigned short target);
unsigned short copyBitWord(const unsigned short * chkBit, const unsigned short * resultBit, size_t size, unsigned short target);
unsigned long copyBitDWord(const unsigned short * chkBit, const unsigned long * resultBit, size_t size, unsigned short target);

size_t copyByte(union Byte dst[], const union Byte src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyWord(union Word dst[], const union Word src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);
size_t copyDWord(union DWord dst[], const union DWord src[], const unsigned short dstIDs[], const unsigned short srcIDs[], size_t dstCount, size_t srcCount);

void SimpleAlloc_init(unsigned long buff[], size_t count);
void * SimpleAlloc_new(unsigned long buff[], size_t count, size_t byte_size);

struct DataRecordCtrol
{
    union DWord *           buff;
    const unsigned short *  ids;
    size_t                  dwordCount;
    size_t                  wordCount;
    size_t                  byteCount;
};
void RecCtrl_init(struct DataRecordCtrol * obj, union DWord * buff, const unsigned short * ids, const unsigned short * cnt, size_t dwMaxID, size_t wMaxID, size_t bMaxID);
void RecCtrl_setInitData(struct DataRecordCtrol * obj, const unsigned long tbl_dw[], const unsigned short tbl_w[], const unsigned char tbl_b[], size_t dwordMaxIDs, size_t wordMaxIDs, size_t byteMaxIDs);
unsigned char RecCtrl_dataSize(struct DataRecordCtrol * obj, unsigned short key);
void RecCtrl_copy(struct DataRecordCtrol * dst, const struct DataRecordCtrol * src);
union DWord * RecCtrl_get(struct DataRecordCtrol * obj, unsigned short key);

struct RecStreamCtrl
{
    struct DataRecordCtrol * rec;
    const unsigned short *   fmt;
    union DWord *            pram;
    size_t                   idx;
    size_t                   cnt;
    size_t                   max;
    unsigned char            pos;
    unsigned char            dsz;
};
void RecStreamCtrl_init(struct RecStreamCtrl * stm, struct DataRecordCtrol * rec, const unsigned short * fmt, size_t fmtCnt);
size_t RecStreamCtrl_Size(struct RecStreamCtrl * stm);
void RecStreamCtrl_in(struct RecStreamCtrl * stm, unsigned char data);
void RecStreamCtrl_inl(struct RecStreamCtrl * stm, unsigned char data);
unsigned char RecStreamCtrl_get(struct RecStreamCtrl * stm);
unsigned char RecStreamCtrl_getl(struct RecStreamCtrl * stm);

unsigned char calcOfRingBuffCount(unsigned char top, unsigned char tail, unsigned char max);

/* CRC16 */
union Word swapByteOfWord(union Word src);
union Word calcCRC16_in(const unsigned short tbl[], union Word crc, unsigned char data);
unsigned short calcCRC16(const unsigned short tbl[], const unsigned char * data, unsigned short size);

#ifdef __cplusplus
};
#endif

/* -----<< Escape Code >>----- */
/* screen clear */
extern const char * scrClearCurBack;                    /* screen clear of back on cursor               */
extern const char * scrClearCurFront;                   /* screen clear of front on cursor              */
extern const char * scrClear;                           /* screen clear                                 */
extern const char * lineClearCurBack;                   /* line clear of back on cursor                 */
extern const char * lineRemoveCurFront;                 /* line clear of front on cursor                */
extern const char * lineRemove;                         /* line clear                                   */
/* font attribute */
extern const char * fontReset;                          /* font attribute reset                         */
extern const char * fontBold;                           /* font attribute of bold                       */
extern const char * fontThin;                           /* font attribute of thin                       */
extern const char * fontItalic;                         /* font attribute of itaic                      */
extern const char * fontUnderLine;                      /* font attribute of under line                 */
extern const char * fontBlink;                          /* font attribute of blink                      */
extern const char * fontHiBlink;                        /* font attribute of hi speed blink             */
extern const char * fontColorReverse;                   /* reverse of color on font attribute           */
extern const char * fontHide;                           /* Hide of font                                 */
extern const char * fontStrikethrough;                  /* strikethrough of font attribute              */
/* font color */
extern const char * fontBlack;
extern const char * fontRed;
extern const char * fontGreen;
extern const char * fontYellow;
extern const char * fontBlue;
extern const char * fontMagellan;
extern const char * fontCyan;
extern const char * fontWhite;
extern const char * fontBlackBack;
extern const char * fontRedBack;
extern const char * fontGreenback;
extern const char * fontYellowBack;
extern const char * fontBlueBack;
extern const char * fontMagellanBack;
extern const char * fontCyanBack;
extern const char * fontWhiteBack;
extern const char * fontColorCode;                      /* font color code(0-255)                       */
extern const char * fontColorCodeBack;                  /* Back color code(0-255)                       */
extern const char * fontRGB;                            /* font color code(R,G,B)                       */
extern const char * fontRGBBack;                        /* Back color code(R,G,B)                       */
/* cursor move */
extern const char * curUP;                              /* 1 up of cursor                               */
extern const char * curDown;                            /* 1 down of cursor                             */
extern const char * curRtiht;                           /* 1 right of cursor                            */
extern const char * curLeft;                            /* 1 left of cursor                             */
extern const char * curUpLineTop;                       /* move to 1 up line top                        */
extern const char * curDownLineTop;                     /* move to 1 down line top                      */
extern const char * curMoveLeft;                        /* move to %d on left origin                    */
extern const char * curMoveTopLeft;                     /* move to n(%d), m(%d) on top ant left origin  */
/* Scroll */
extern const char * curUpScroll;                        /* 1 line up scroll                             */
extern const char * curUpScrolln;                       /* %d line up scroll                            */
extern const char * curDownScroll;                      /* 1 line down scroll                           */
extern const char * curDownScrolln;                     /* %d line down scroll                          */

#define __MAX(a, b) ((a) > (b) ? (a) : (b))
#define __Count(tbl) (sizeof(tbl)/sizeof(tbl[0]))


#endif
