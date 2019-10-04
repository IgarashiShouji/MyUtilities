#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require 'spreadsheet'

# analisys class of data sheet
class DataRecord
  @prefix;
  @out_print

  # set prefix string
  def setPrefix(str)
    @prefix = str
  end

  # constructor
  def initialize()
    @prefix=""
    @out_print = true;
    # ----<< enum >>----
    @dword = Array.new    # enum list of 4 byte data
    @word  = Array.new    # enum list of 2 byte data
    @byte  = Array.new    # enum list of 1 byte data
    @rdef  = Hash.new     # redefine talbe

    # ----<< init value >>----
    @dwVal = Array.new    # initial values of 4 byte data
    @wVal  = Array.new    # initial values of 2 byte data
    @bVal  = Array.new    # initial values of 1 byte data

    # ----<< init string >>----
    @dwStr = Array.new    # string list of 4 byte data
    @wStr  = Array.new    # string list of 2 byte data
    @bStr  = Array.new    # string list of 1 byte data

    # ----<< record list >>----
    @rec   = Hash.new     # record list
    @rec_dw= Hash.new     # item count of 4 byte data in record
    @rec_w = Hash.new     # item count of 2 byte data in record
    @rec_b = Hash.new     # item count of 1 byte data in record

    # ----<< group ist >>----
    @group = Hash.new     # group list

    # ----<< transaction ist >>----
    @trs    = Hash.new      # transaction list
    @trs_key= Array.new
  end

  # read data sheet
  def read(readName)
    readBook = Spreadsheet.open(readName)
    readSheet = readBook.worksheet('Data')
    # get record list
    for column in 8..65535 do
      if nil != readSheet[0, column] then
        key = String.new(readSheet[0, column]);
        @rec[key] = Array.new
        @rec_dw[key] = Array.new;
        @rec_w[key]  = Array.new;
        @rec_b[key]  = Array.new;
      else
        break;
      end
    end
    # get data list
    for row in 2..65535 do
      if nil != readSheet[row, 1] then
        if readSheet[row, 2] =~ /float/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /uint32/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /int32/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /uint16/ then
          pushWord(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /int16/ then
          pushWord(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /uint8/ then
          pushByte(readSheet, row)
          next;
        end
        if readSheet[row, 2] =~ /int8/ then
          pushByte(readSheet, row)
        end
      else
        break
      end
    end

    # get transaction list
    readSheet = readBook.worksheet('Data')
    for column in 8..65535 do
      if nil != readSheet[0, column] then
        key = String.new(readSheet[0, column])
        @trs[key] = Hash.new
        @trs_key.push(key)
      else
        break;
      end
    end
    for row in 2..65535 do
      if nil != readSheet[row, 1] then
        @trs_key.each_with_index do |trs, idx|
          if nil != readSheet[row, 8+idx] then
            key = readSheet[row, 8+idx]
            (@trs[trs])[key] = readSheet[row, 1]
          end
        end
      else
        break;
      end
    end

    # get Group list
    readSheet = readBook.worksheet('Group')
    for row in 2..65535 do
      if nil != readSheet[row, 1] then
        gname = readSheet[row, 1];
        @group[gname] = Array.new
        #print readSheet[row,1], "\n"
        for column in 4..65535 do
          if nil != readSheet[0, column] then
            if nil != readSheet[row, column] then
              (@group[gname]).push(readSheet[0, column])
              #print readSheet[0,column], "\n"
            end
          else
            break;
          end
        end
      else
        break;
      end
    end
  end

protected
  # sace record infomation
  def pushRec(readSheet, row, recHash)
    column = 8;
    (@rec.keys).each do |key|
      if nil != readSheet[row, column] then
        (@rec[key]).push(String.new(readSheet[row, 1]))
        recHash[key].push(String.new(readSheet[row, 1]))
      end
      column += 1;
    end
  end

  # save 4 byte data infomation
  def pushDWord(readSheet, row)
    @dword.push(String.new(readSheet[row, 1]))
    if nil != readSheet[row, 4] then
      @rdef[String.new(readSheet[row, 1])] = String.new(readSheet[row, 4])
    end
    if nil != readSheet[row, 3] then
      @dwVal.push(readSheet[row, 3]);
    else
      if nil == readSheet[row, 4] then
        @dwVal.push(0);
      end
    end
    if nil != readSheet[row, 4] then
      str = String.new(readSheet[row, 4]);
      @dwStr.push(str);
      if nil == readSheet[row, 3] then
        @dwVal.push(str.size());
      end
    else
      @dwStr.push("");
    end
    pushRec(readSheet, row, @rec_dw)
  end

  # save 2 byte data infomation
  def pushWord(readSheet, row)
    @word.push(String.new(readSheet[row, 1]))
    if nil != readSheet[row, 4] then
      @rdef[String.new(readSheet[row, 1])] = String.new(readSheet[row, 4])
    end
    if nil != readSheet[row, 3] then
      @wVal.push(readSheet[row, 3]);
    else
      if nil == readSheet[row, 4] then
        @wVal.push(0);
      end
    end
    if nil != readSheet[row, 4] then
      str = String.new(readSheet[row, 4]);
      @wStr.push(str);
      if nil == readSheet[row, 3] then
        @wVal.push(str.size());
      end
    else
      @wStr.push("");
    end
    pushRec(readSheet, row, @rec_w)
  end

  # save 1 byte data infomation
  def pushByte(readSheet, row)
    @byte.push(String.new(readSheet[row, 1]))
    if nil != readSheet[row, 4] then
      @rdef[String.new(readSheet[row, 1])] = String.new(readSheet[row, 4])
    end
    if nil != readSheet[row, 3] then
      @bVal.push(readSheet[row, 3]);
    else
      if nil == readSheet[row, 4] then
        @bVal.push(0);
      end
    end
    if nil != readSheet[row, 4] then
      str = String.new(readSheet[row, 4]);
      @bStr.push(str);
      if nil == readSheet[row, 3] then
        @bVal.push(str.size());
      end
    else
      @bStr.push("");
    end
    pushRec(readSheet, row, @rec_b)
  end

public
  # print enum code
  def printEnum
    cnt = 0;
    pre = ''
    prefix = 1;
    print "enum ", @prefix, "DataIDs", "\n"
    print "{", "\n"
    @dword.each do |item|
      if 126 < cnt then
        print "};", "\n"
        printf("enum %sDataIDs%d\n", @prefix, prefix);
        print "{", "\n"
        printf("    %sDataIDs%d_begin = %s,\n", @prefix, prefix, pre);
        print "    ", item, ",\n"
        cnt = 0;
        prefix += 1;
      else
        print "    ", item, ",\n"
        pre = item;
      end
      cnt += 1;
    end
    @word.each do |item|
      if 126 < cnt then
        print "};", "\n"
        printf("enum %sDataIDs%d\n", @prefix, prefix);
        print "{", "\n"
        printf("    %sDataIDs%d_begin = %s,\n", @prefix, prefix, pre);
        print "    ", item, ",\n"
        cnt = 0;
        prefix += 1;
      else
        print "    ", item, ",\n"
        pre = item;
      end
      cnt += 1;
    end
    @byte.each do |item|
      if 126 < cnt then
        print "};", "\n"
        printf("enum %sDataIDs%d\n", @prefix, prefix);
        print "{", "\n"
        printf("    %sDataIDs%d_begin = %s,\n", @prefix, prefix, pre);
        print "    ", item, ",\n"
        cnt = 0;
        prefix += 1;
      else
        print "    ", item, ",\n"
        pre = item;
      end
      cnt += 1;
    end
    print "    ", @prefix, "ID_MAX", ",\n\n"
    print "    ", @prefix, "ID_DWORD_BEGIN = ", @dword[0], ",\n"
    print "    ", @prefix, "ID_DWORD_MAX   = ", @word[0], ",\n"
    print "    ", @prefix, "ID_WORD_BEGIN  = ", @word[0], ",\n"
    print "    ", @prefix, "ID_WORD_MAX    = ", @byte[0], ",\n"
    print "    ", @prefix, "ID_BYTE_BEGIN  = ", @byte[0], ",\n"
    print "    ", @prefix, "ID_BYTE_MAX    = ", @prefix, "ID_MAX", ",\n"
    print "    ", @prefix, "ID_DWORD_CNT = ", @dword.size, ",\n"
    print "    ", @prefix, "ID_WORD_CNT  = ", @word.size, ",\n"
    print "    ", @prefix, "ID_BYTE_CNT  = ", @byte.size, "\n"
    print "};", "\n"
    print "extern const unsigned long ", @prefix, "tblInitDWord[", @dwVal.size(), "];\n"
    print "extern const unsigned short ", @prefix, "tblInitWord[", @wVal.size(), "];\n"
    print "extern const unsigned char ", @prefix, "tblInitByte[", @bVal.size(), "];\n"
  end

  # print initial value code
  def printInit
    print "const unsigned long ", @prefix, "tblInitDWord[", @dwVal.size(), "] = ", "\n"
    print "{", "\n"
    @dwVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "const unsigned short ", @prefix, "tblInitWord[", @wVal.size(), "] = ", "\n"
    print "{", "\n"
    @wVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "const unsigned char ", @prefix, "tblInitByte[", @bVal.size(), "] = ", "\n"
    print "{", "\n"
    @bVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
  end

  def setSrintOutput(mode)
    @out_print = mode;
  end
  # print string list code
  def printString
    if @out_print then
      print "static const char * const ", @prefix, "tblStringDWord[", (@dwStr.size() + @wStr.size() + @bStr.size()), "] = ", "\n"
      print "{", "\n"
      @dwStr.each do |item|
        print '    "', item, '"', ",\n"
      end
      @wStr.each do |item|
        print '    "', item, '"', ",\n"
      end
      @bStr.each do |item|
        print '    "', item, '"', ",\n"
      end
      print "};", "\n"
    end
  end

  # print record enum information code
  def printRecEnum()
    print 'enum ', @prefix,'RecordIDs', "\n"
    print '{', "\n"
    (@rec.keys).each do |name|
      print '    ', name, ",\n"
    end
    print '    ', @prefix, 'REC_MAX', ",\n\n"
    (@rec.keys).each do |name|
      print '    ', @prefix, 'RCNT_', name, ' = (', (@rec[name]).length, "),\n"
    end
    (@rec.keys).each do |name|
      print '    ', @prefix, 'RSZ_DW_', name, ' = (', @rec_dw[name].length, "),\n"
    end
    (@rec.keys).each do |name|
      print '    ', @prefix, 'RSZ_W_', name, ' = (', @rec_w[name].length, "),\n"
    end
    (@rec.keys).each do |name|
      print '    ', @prefix, 'RSZ_B_', name, ' = (', @rec_b[name].length, "),\n"
    end
    (@rec.keys).each do |name|
      size  = @rec_dw[name].length
      size += @rec_w[name].length / 2
      if 0 < (@rec_w[name].length % 2) then
        size += 1
      end
      size += @rec_b[name].length / 4
      if 0 < (@rec_b[name].length % 4) then
        size += 1
      end
      print '    ', @prefix, 'RSZ_', name, ' = (', size, "),\n"
    end
    print '};', "\n"
    print 'extern const unsigned short * const ', @prefix, 'tblRecIDs[', (@rec.keys).length, '];', "\n"
    print 'extern const unsigned short ', @prefix, 'tblRecSize[', (@rec.keys).length+1, '][4];', "\n"
    print 'extern const struct RecordInfomation ', @prefix, 'tblRecInfo;', "\n"
  end

  # print transaction infomation
  def printTrsHeader()
    (@trs.keys).each do |trs|
      printf("extern const unsigned short %strs_%s[%d];\n", @prefix, trs, (@trs[trs]).keys.length)
    end
  end

  # print redefine convert table header
  def printReDefHeader()
    printf("extern const unsigned short %stblDefKeys[%d];\n",   @prefix, @rdef.length)
    printf("extern const unsigned short %stbleReDef[%d];\n",    @prefix, @rdef.length)
    printf("extern const unsigned short %stblReDefKeys[%d];\n", @prefix, @rdef.length)
    printf("extern const unsigned short %stbleDef[%d];\n",      @prefix, @rdef.length)
  end

  # print record list code
  def printRec()
    (@rec.keys).each do |name|
      print "static const unsigned short ", @prefix, "tblRec_", name, "[", (@rec[name]).length, "] =\n"
      print "{\n"
      (@rec_dw[name]).each do |item|
        print '    ', item, ",\n"
      end
      (@rec_w[name]).each do |item|
        print '    ', item, ",\n"
      end
      (@rec_b[name]).each do |item|
        print '    ', item, ",\n"
      end
      print "};\n"
    end
    print 'const unsigned short * const ', @prefix, 'tblRecIDs[', (@rec.keys).length, '] =', "\n"
    print '{', "\n"
    (@rec.keys).each do |name|
      print 
      print '    &(', @prefix, 'tblRec_', name, '[0]),', "\n"
    end
    print '};', "\n"
  end

  # print record Size
  def printRecSize()
    print 'const unsigned short ', @prefix, 'tblRecSize[', (@rec.keys).length+1, '][4] =', "\n"
    print "{\n"
    (@rec.keys).each do |name|
      size  = @rec_dw[name].length
      size += @rec_w[name].length / 2
      if 0 < (@rec_w[name].length % 2) then
        size += 1
      end
      size += @rec_b[name].length / 4
      if 0 < (@rec_b[name].length % 4) then
        size += 1
      end
      printf("    { %3d, ", (@rec_dw[name].length + @rec_w[name].length + @rec_b[name].length));
      printf("%2d, %2d, %2d },\n", @rec_dw[name].length, @rec_w[name].length, @rec_b[name].length )
    end
    print '    { ', @prefix, 'ID_MAX, ', @prefix, 'ID_DWORD_CNT, ', @prefix, 'ID_WORD_CNT, ', @prefix, 'ID_BYTE_CNT }', "\n"
    print '};', "\n"
  end
  def printRecInfo
    print 'const struct RecordInfomation ', @prefix, 'tblRecInfo =', "\n"
    print '{', "\n"
    print '    ', @prefix, 'ID_DWORD_CNT,', "\n"
    print '    ', @prefix, 'ID_WORD_CNT,', "\n"
    print '    ', @prefix, 'ID_BYTE_CNT,', "\n"
    print '    ', (@rec.keys).length, ",\n"
    print '    &(', @prefix, 'tblRecIDs[0]),', "\n"
    print '    &(', @prefix, 'tblRecSize[0][0])', "\n"
    print '};', "\n"
  end

  # print Group Header Information
  def printGroup()
    print 'enum ', @prefix, 'GroupIDs', "\n"
    print "{\n"
    (@group.keys).each do |gname|
      print '    ', gname, ",\n"
    end
    print "    ", @prefix, "GROUPID_MAX,\n"
    print "\n"
    (@group.keys).each do |gname|
      cnt = 0;
      (@group[gname]).each do |rname|
        if nil != @rec[rname] then
          cnt += (@rec[rname]).length
        else
          print "Record Name Error: ", rname, "\n"
        end
      end
      print '    ', gname, '_RecCntSum', ' = (', cnt, "),\n"
    end
    print "\n"
    (@group.keys).each do |gname|
      max = 0;
      (@group[gname]).each do |rname|
        if max < (@rec[rname]).length then
          max = (@rec[rname]).length
        end
      end
      print '    ', gname, '_RecCntMax', ' = (', max, "),\n"
    end
    print "};\n"
  end

  # print Transaction List Code
  def printTRS()
    (@trs.keys).each do |trs|
      printf("const unsigned short %strs_%s[%d] =\n", @prefix, trs, (@trs[trs]).keys.length)
      printf("{\n");
      ((@trs[trs]).keys.sort).each do |key|
        #print trs, "[", key, "]: ", (@trs[trs])[key], "\n"
        printf("    %s,\n", (@trs[trs])[key])
      end
      printf("};\n");
    end
  end
  def printClass()
    print '#ifdef __cplusplus', "\n"
    print '#include "Entity.hpp"', "\n"
    print 'namespace ', @prefix, 'MyEntity', "\n"
    print '{', "\n"
    print '    class DataRec', "\n"
    print '    {', "\n"
    print '    private:', "\n"
    print '        MyEntity::DataRecord rec;', "\n"
    print '    public:', "\n"
    print '        inline DataRec(union DWord * buff, size_t recID);', "\n"
    print '        inline ~DataRec(void);', "\n"
    print '        inline MyEntity::ConstArrayMap<union DWord, unsigned short> & getDWordList(void);', "\n"
    print '        inline MyEntity::ConstArrayMap<union Word,  unsigned short> & getWordList(void);', "\n"
    print '        inline MyEntity::ConstArrayMap<union Byte,  unsigned short> & getByteList(void);', "\n"
    print '        inline unsigned char dataSize(unsigned short key) const;', "\n"
    print '        inline DataRec & operator = (MyEntity::DataRecord & src);', "\n"
    print '        inline union DWord & operator [](unsigned short key);', "\n"
    print '        inline MyEntity::DataRecord & operator *(void);', "\n"
    print '    };', "\n"
    print '    DataRec::DataRec(union DWord * buff, size_t recID)', "\n"
    print '      : rec(buff, ', @prefix, 'tblRecIDs[recID], ', @prefix, 'tblRecSize[recID], ', @prefix, 'ID_DWORD_MAX, ', @prefix, 'ID_WORD_MAX, ', @prefix, 'ID_BYTE_MAX)', "\n"
    print '    {', "\n"
    print '    }', "\n"
    str = <<-EOS
    DataRec::~DataRec(void)
    {
    }
    MyEntity::ConstArrayMap<union DWord, unsigned short> & DataRec::getDWordList(void)
    {
        return rec.getDWordList();
    }
    MyEntity::ConstArrayMap<union Word,  unsigned short> & DataRec::getWordList(void)
    {
        return rec.getWordList();
    }
    MyEntity::ConstArrayMap<union Byte,  unsigned short> & DataRec::getByteList(void)
    {
        return rec.getByteList();
    }
    unsigned char DataRec::dataSize(unsigned short key) const
    {
        return rec.dataSize(key);
    }
    DataRec & DataRec::operator = (MyEntity::DataRecord & src)
    {
        rec = src;
        return *this;
    }
    union DWord & DataRec::operator [](unsigned short key)
    {
        return rec[key];
    }
    MyEntity::DataRecord & DataRec::operator *(void)
    {
        return rec;
    }
};
#define RecTable(val, T, buff) val(buff, tblRecIDs[ T ], tblRecSize[ T ], ID_DWORD_MAX, ID_WORD_MAX, ID_BYTE_MAX);
#endif
EOS
    print "\n"
    print str;
  end

  # print redefine prepro code
  def printReDefTool(hfile)
    head = <<-EOS
#include <stdio.h>

int main(int argc, char * argv[])
{
EOS
    tail = <<-EOS
    return 0;
}
EOS
    print '#include "', hfile, '"', "\n"
    print head
    (@rdef.keys).each do |item|
      print '    printf("%08x:', item, ',', @rdef[item], '\n", ', @rdef[item], ');', "\n"
    end
    print tail
  end

  # print redefine table
  def printReDef(cmd)
    list = Array.new
    IO.popen(cmd, "r+") do |io|
      io.each do |str|
        str.chop!()
        list.push(str);
      end
    end
    printf("const unsigned short %stblDefKeys[%d] =\n", @prefix, list.length)
    print "{\n"
    list.each do |str|
      item  = str.split(/,/)
      item2 = item[0].split(/:/)
      printf("    %-30s /* %-30s */\n", item2[1]+',', item[1])
    end
    print "};\n"
    printf("const unsigned short %stbleReDef[%d] =\n", @prefix, list.length)
    print "{\n"
    list.each do |str|
      item  = str.split(/,/)
      item2 = item[0].split(/:/)
      printf("    %-30s /* %-30s */\n", item[1]+',', item2[1])
    end
    print "};\n"
    list.sort!()
    printf("const unsigned short %stblReDefKeys[%d] =\n", @prefix, list.length)
    print "{\n"
    list.each do |str|
      item = str.split(/,/)
      printf("    %-30s /* %-30s */\n", item[1]+',', item[0])
    end
    print "};\n"
    printf("const unsigned short %stbleDef[%d] =\n", @prefix, list.length)
    print "{\n"
    list.each do |str|
      item  = str.split(/,/)
      item2 = item[0].split(/:/)
      printf("    %-30s /* %-30s */\n", item2[1]+',', item[1])
    end
    print "};\n"
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  drec = DataRecord.new
  drec.read(ARGV.shift())
  mode    = "all"
  str_prn = true
  header  = Array.new()
  ARGV.each do |item|
    case item
    when '--hpp' then
      mode=item
    when '--cpp' then
      mode=item
    when '--redefine' then
      mode=item
    when '--no-string' then
      drec.setSrintOutput(false)
    else
      if item =~ /--prefix=/ then
        drec.setPrefix(item.gsub(/--prefix=/, ''))
      elsif item =~ /--header=/ then
        header.push(item.gsub(/--header=/, ''))
      elsif item =~ /--ReDefCode=/ then
        drec.printReDefTool(item.gsub(/--ReDefCode=/, ''))
        exit 0
      elsif item =~ /--redefine=/ then
        drec.printReDef(item.gsub(/--redefine=/, ''))
        exit 0
      else
      end
    end
  end
  if 0 < header.length then
    case mode
    when '--hpp' then
      self_head = header.shift()
      print '#ifndef __', self_head, '_h__', "\n"
      print '#define __', self_head, '_h__', "\n"
      print "\n"
      print '#include "MyUtilities.h"', "\n"
      print "\n"
      print "\n"
      print "/**\n * Data IDs\n */\n"
      drec.printEnum()
      print "\n"
      print "/**\n * Record infomation\n */\n"
      drec.printRecEnum()
      print "\n"
      print "/**\n * Group infomation\n */\n"
      drec.printGroup()
      print "\n"
      print "/**\n * Transaction infomation\n */\n"
      drec.printTrsHeader()
      print "\n"
      print "/**\n * ReDefine infomation\n */\n"
      drec.printReDefHeader()
      drec.printClass()
      print "\n"
      print "\n"
      print '#endif', "\n"
    when '--cpp' then
      header.each do |item|
        print '#include "', item, '.h"', "\n"
      end
      print "\n"
      drec.printInit()
      drec.printString()
      drec.printRec()
      drec.printRecSize()
      drec.printRecInfo()
      drec.printTRS()
    else
      header.shift()
      header.each do |item|
        print '#include "', item, '.h"', "\n"
      end
      drec.printEnum()
      drec.printRecEnum()
      drec.printGroup()
      drec.printTrsHeader()
      drec.printInit()
      drec.printString()
      drec.printRec()
      drec.printRecSize()
      drec.printTRS()
    end
  end
end
