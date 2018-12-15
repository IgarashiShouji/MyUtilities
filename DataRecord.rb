#! /usr/bin/ruby

require 'spreadsheet'

class DataRecord
  def initialize()
    # ----<< enum >>----
    @dword = Array.new
    @word  = Array.new
    @byte  = Array.new
    # ----<< init value >>----
    @dwVal = Array.new
    @wVal  = Array.new
    @bVal  = Array.new
    # ----<< init string >>----
    @dwStr = Array.new
    @wStr  = Array.new
    @bStr  = Array.new
    # ----<< record list >>----
    @rec   = Hash.new

  end
  def read(readName)
    readBook = Spreadsheet.open(readName)
    readSheet = readBook.worksheet('Data Define')
    for column in 5..65535 do
      if nil != readSheet[0,column] then
        key = String.new(readSheet[0,column]);
        @rec[key] = Array.new
      else
        break;
      end
    end
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
  def pushRec(readSheet, row)
    column = 5;
    (@rec.keys).each do |key|
      if nil != readSheet[row, column] then
        (@rec[key]).push(String.new(readSheet[row,1]))
      end
      column += 1;
    end
  end
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
    pushRec(readSheet, row)
  end
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
    pushRec(readSheet, row)
  end
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
    pushRec(readSheet, row)
  end
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
    print "    ID_DWORD_BEGIN = ", @dword[0], ",\n"
    print "    ID_DWORD_MAX   = ", @word[0], ",\n"
    print "    ID_WORD_BEGIN  = ", @word[0], ",\n"
    print "    ID_WORD_MAX    = ", @byte[0], ",\n"
    print "    ID_BYTE_BEGIN  = ", @byte[0], ",\n"
    print "    ID_BYTE_MAX    = DataID_MAX", ",\n"
    print "    ID_DWORD_CNT = ", @dword.size, ",\n"
    print "    ID_WORD_CNT  = ", @word.size, ",\n"
    print "    ID_BYTE_CNT  = ", @byte.size, "\n"
    print "};", "\n"
  end
  def printInit
    print "static const unsigned long tblInitDWord[", @dwVal.size(), "] = ", "\n"
    print "{", "\n"
    @dwVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "static const unsigned short tblInitWord[", @wVal.size(), "] = ", "\n"
    print "{", "\n"
    @wVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
    print "static const unsigned char tblInitByte[", @bVal.size(), "] = ", "\n"
    print "{", "\n"
    @bVal.each do |item|
      print "    ", item, ",\n"
    end
    print "};", "\n"
  end
  def printString
    print "static const unsigned long tblStringDWord[", @dwVal.size(), "] = ", "\n"
    print "{", "\n"
    @dwStr.each do |item|
      print '    "', item, '"', ",\n"
    end
    print "};", "\n"
    print "static const unsigned short tblStringWord[", @wVal.size(), "] = ", "\n"
    print "{", "\n"
    @wStr.each do |item|
      print '    "', item, '"', ",\n"
    end
    print "{", "\n"
    print "static const unsigned char tblStringByte[", @bVal.size(), "] = ", "\n"
    print "{", "\n"
    @bStr.each do |item|
      print '    "', item, '"', ",\n"
    end
    print "};", "\n"
  end
  def printRec()
    (@rec.keys).each do |name|
      print "static const unsigned short tblRec_", name, "[", (@rec[name]).length, "] =\n"
      print "{\n"
      (@rec[name]).each do |item|
        print "    ", item, ",\n"
      end
      print "};\n"
    end
  end
end

if $0 == __FILE__ then
  drec = DataRecord.new
  drec.read('DataRecord.xls')
  drec.printEnum();
  drec.printInit();
  drec.printString();
  drec.printRec();
end
