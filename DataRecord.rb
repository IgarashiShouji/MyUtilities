#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require 'spreadsheet'

# analisys class of data sheet
class DataRecord
  # constructor
  def initialize()
    # ----<< enum >>----
    @dword = Array.new    # enum list of 4 byte data
    @word  = Array.new    # enum list of 2 byte data
    @byte  = Array.new    # enum list of 1 byte data

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
  end

  # read data sheet
  def read(readName)
    readBook = Spreadsheet.open(readName)
    readSheet = readBook.worksheet('Data Define')
    # get record list
    for column in 6..65535 do
      if nil != readSheet[0,column] then
        key = String.new(readSheet[0,column]);
        @rec[key] = Array.new
        @rec_dw[key] = 0;
        @rec_w[key]  = 0;
        @rec_b[key]  = 0;
      else
        break;
      end
    end
    # get data list
    for row in 2..65535 do
      if nil != readSheet[row,1] then
        if readSheet[row,2] =~ /float/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /uint32/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /int32/ then
          pushDWord(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /uint16/ then
          pushWord(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /int16/ then
          pushWord(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /uint8/ then
          pushByte(readSheet, row)
          next;
        end
        if readSheet[row,2] =~ /int8/ then
          pushByte(readSheet, row)
        end
      else
        break
      end
    end
  end

protected
  # sace record infomation
  def pushRec(readSheet, row, recCnt)
    column = 6;
    (@rec.keys).each do |key|
      if nil != readSheet[row, column] then
        (@rec[key]).push(String.new(readSheet[row,1]))
        recCnt[key] += 1;
      end
      column += 1;
    end
  end

  # save 4 byte data infomation
  def pushDWord(readSheet, row)
    @dword.push(String.new(readSheet[row,1]))
    if nil != readSheet[row,3] then
      @dwVal.push(readSheet[row,3]);
    else
      if nil == readSheet[row,4] then
        @dwVal.push(0);
      end
    end
    if nil != readSheet[row,4] then
      str = String.new(readSheet[row,4]);
      @dwStr.push(str);
      if nil == readSheet[row,3] then
        @dwVal.push(str.size());
      end
    else
      @dwStr.push("");
    end
    pushRec(readSheet, row, @rec_dw)
  end

  # save 2 byte data infomation
  def pushWord(readSheet, row)
    @word.push(String.new(readSheet[row,1]))
    if nil != readSheet[row,3] then
      @wVal.push(readSheet[row,3]);
    else
      if nil == readSheet[row,4] then
        @wVal.push(0);
      end
    end
    if nil != readSheet[row,4] then
      str = String.new(readSheet[row,4]);
      @wStr.push(str);
      if nil == readSheet[row,3] then
        @wVal.push(str.size());
      end
    else
      @wStr.push("");
    end
    pushRec(readSheet, row, @rec_w)
  end

  # save 1 byte data infomation
  def pushByte(readSheet, row)
    @byte.push(String.new(readSheet[row,1]))
    if nil != readSheet[row,3] then
      @bVal.push(readSheet[row,3]);
    else
      if nil == readSheet[row,4] then
        @bVal.push(0);
      end
    end
    if nil != readSheet[row,4] then
      str = String.new(readSheet[row,4]);
      @bStr.push(str);
      if nil == readSheet[row,3] then
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
    print "enum DataIDs", "\n"
    print "{", "\n"
    @dword.each do |item|
      print "    ID_", item, ",\n"
    end
    @word.each do |item|
      print "    ID_", item, ",\n"
    end
    @byte.each do |item|
      print "    ID_", item, ",\n"
    end
    print "    ID_MAX", ",\n\n"
    print "    ID_DWORD_BEGIN = ID_", @dword[0], ",\n"
    print "    ID_DWORD_MAX   = ID_", @word[0], ",\n"
    print "    ID_WORD_BEGIN  = ID_", @word[0], ",\n"
    print "    ID_WORD_MAX    = ID_", @byte[0], ",\n"
    print "    ID_BYTE_BEGIN  = ID_", @byte[0], ",\n"
    print "    ID_BYTE_MAX    = ID_MAX", ",\n"
    print "    ID_DWORD_CNT = ", @dword.size, ",\n"
    print "    ID_WORD_CNT  = ", @word.size, ",\n"
    print "    ID_BYTE_CNT  = ", @byte.size, "\n"
    print "};", "\n"
    print "extern const unsigned long tblInitDWord[", @dwVal.size(), "];\n"
    print "extern const unsigned short tblInitWord[", @wVal.size(), "];\n"
    print "extern const unsigned char tblInitByte[", @bVal.size(), "];\n"
  end

  # print initial value code
  def printInit
    print "const unsigned long tblInitDWord[", @dwVal.size(), "] = ", "\n"
    print "{", "\n"
    @dwVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "const unsigned short tblInitWord[", @wVal.size(), "] = ", "\n"
    print "{", "\n"
    @wVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "const unsigned char tblInitByte[", @bVal.size(), "] = ", "\n"
    print "{", "\n"
    @bVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
  end

  # print string list code
  def printString
    print "static const char * const tblStringDWord[", (@dwStr.size() + @wStr.size() + @bStr.size()), "] = ", "\n"
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

  # print record enum information code
  def printRecEnum()
    print 'enum RecordIDs', "\n"
    print '{', "\n"
    (@rec.keys).each do |name|
      print '    REC_', name, ",\n"
    end
    print '    REC_MAX', ",\n"
    (@rec.keys).each do |name|
      print '    RCNT_', name, ' = (', (@rec[name]).length, "),\n"
    end
    (@rec.keys).each do |name|
      print '    RSZ_DW_', name, ' = (', @rec_dw[name], "),\n"
    end
    (@rec.keys).each do |name|
      print '    RSZ_W_', name, ' = (', @rec_w[name], "),\n"
    end
    (@rec.keys).each do |name|
      print '    RSZ_B_', name, ' = (', @rec_b[name], "),\n"
    end
    (@rec.keys).each do |name|
      size  = @rec_dw[name]
      size += @rec_w[name] / 2
      if 0 < (@rec_w[name] % 2) then
        size += 1
      end
      size += @rec_b[name] / 4
      if 0 < (@rec_b[name] % 4) then
        size += 1
      end
      print '    RSZ_', name, ' = (', size, "),\n"
    end
    print '};', "\n"
    print 'extern const unsigned short * const tblRecIDs[', (@rec.keys).length, '];', "\n"
    print 'extern const unsigned short tblRecSize[', (@rec.keys).length, '][4];', "\n"
  end

  # print record list code
  def printRec()
    (@rec.keys).each do |name|
      print "static const unsigned short tblRec_", name, "[", (@rec[name]).length, "] =\n"
      print "{\n"
      (@rec[name]).each do |item|
        print "    ID_", item, ",\n"
      end
      print "};\n"
    end
    print 'const unsigned short * const tblRecIDs[', (@rec.keys).length, '] =', "\n"
    print '{', "\n"
    (@rec.keys).each do |name|
      print 
      print '    &(tblRec_', name, '[0]),', "\n"
    end
    print '};', "\n"
  end
  def printRecSize()
    print 'const unsigned short tblRecSize[', (@rec.keys).length, '][4] =', "\n"
    print "{\n"
    (@rec.keys).each do |name|
      size  = @rec_dw[name]
      size += @rec_w[name] / 2
      if 0 < (@rec_w[name] % 2) then
        size += 1
      end
      size += @rec_b[name] / 4
      if 0 < (@rec_b[name] % 4) then
        size += 1
      end
      printf("    { %3d, ", (@rec_dw[name] + @rec_w[name] + @rec_b[name]));
      printf("%2d, %2d, %2d },\n", @rec_dw[name], @rec_w[name], @rec_b[name] )
    end
    print '};', "\n"
  end
end

if $0 == __FILE__ then
  drec = DataRecord.new
  drec.read('DataRecord.xls')
  case ARGV[0]
  when '--hpp' then
    print '#ifndef __DataRecord_h__', "\n"
    print '#define __DataRecord_h__', "\n"
    print "\n"
    drec.printEnum();
    drec.printRecEnum();
    print "\n"
    print "\n"
    print '#endif', "\n"
  when '--cpp' then
    print '#include "DataRecord.h"', "\n"
    print "\n"
    drec.printInit();
    drec.printString();
    drec.printRec();
    drec.printRecSize();
  else
    drec.printEnum();
    drec.printRecEnum();
    drec.printInit();
    drec.printString();
    drec.printRec();
    drec.printRecSize();
  end
end
