#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require 'spreadsheet'

# analisys class of data sheet
class DataRecord
  # constructor
  def initialize()
    @mtx = Mutex.new
    @prefix = ""
    @enum_max = 128

    # sheet position
    @data_row     = 2
    @data_column  = 8
    @group_row    = 2
    @group_column = 8

    # param
    @param_float  = Hash.new
    @param_uint32 = Hash.new
    @param_int32  = Hash.new
    @param_uint16 = Hash.new
    @param_int16  = Hash.new
    @param_uint8  = Hash.new
    @param_int8   = Hash.new

    # recoard, group, aias
    @initval = Hash.new
    @alias   = Hash.new
    @p_str   = Hash.new
    @rec     = Hash.new
    @group   = Hash.new
  end

  def opt(arg)
    arg.each do |str|
      if str =~ /--prefix=/ then
        @prefix = str.gsub(/--prefix=/, '')
      end
    end
  end

  def readParameter(readBook)
    readSheet = readBook.worksheet('Data')
    # get data list
    for row in @data_row..65535 do
      tmp = nil
      @mtx.synchronize do
        tmp = readSheet[row, 1]
      end
      if nil != tmp then
        item = String.new(tmp)
        if(item =~ /[^0-9a-zA-Z_]/)
          printf("Data Sheets (%d, B): \"%s\" is ignore string parameter name\n", (row + 1), item)
          exit -1
        end
        @mtx.synchronize do
          tmp = readSheet[row, 2]
        end
        case tmp
        when "uint32" then
          @param_uint32[row] = item
        when "int32" then
          @param_int32[row]  = item
        when "float" then
          @param_float[row]  = item
        when "uint16" then
          @param_uint16[row] = item
        when "int16" then
          @param_int16[row]  = item
        when "uint8" then
          @param_uint8[row]  = item
        when "int8" then
          @param_int8[row]   = item
        when "group" then
          @group[row]        = item
          next;
        else
          printf("Data Sheets (%d, C): \"%s\" is parameter type error \n", (row + 1), tmp)
          exit -1
        end
        @mtx.synchronize do
          tmp = readSheet[row, 3]
        end
        if nil != tmp then
          item = String.new(tmp.to_s)
          @initval[row] = item
        end
        @mtx.synchronize do
          tmp = readSheet[row, 4]
        end
        if nil != tmp then
          item = String.new(tmp)
          if(item =~ /[^0-9a-zA-Z_\+]/)
            printf("Data Sheets (%d, E): \"%s\" is ignore string alias name\n", (row + 1), item)
            exit -1
          end
          @alias[row] = item
        end
        @mtx.synchronize do
          tmp = readSheet[row, 5]
        end
        if nil != tmp then
          item = String.new(tmp.to_s)
          @p_str[row] = item
        end
      else
        break
      end
    end
  end

  def readRecord(readBook)
    readSheet = readBook.worksheet('Data')
    for column in @data_column..65535 do
      tmp = nil
      @mtx.synchronize do
        tmp = readSheet[0, column]
      end
      if nil != tmp then
        item = String.new(tmp)
        if(item =~ /[^0-9a-zA-Z_]/)
          str = "ABCDEFGHIJKLNMOPQRSTUVWXYZ"
          if(column < str.length) then
            printf("Data Sheets (1, %c): \"%s\" is ignore string record name\n", str[column], item)
          else
            printf("Data Sheets (1, %d): \"%s\" is ignore string record name\n", (column + 1), item)
          end
          exit -1
        end
        @rec[column] = item
      else
        break
      end
    end
  end

  def readRecordParam(readBook)
    recParam = Hash.new
    readSheet = readBook.worksheet('Data')
    param = getPramList()
    (@rec.keys).each do |column|
      rec_name = @rec[column]
      item = Hash.new
      recParam[rec_name] = item
      (param.keys).each do |row|
        tmp = nil
        @mtx.synchronize do
          tmp = readSheet[row, column]
        end
        if nil != tmp then
          item[tmp] = param[row]
        end
      end
    end
    return recParam
  end

  def readGroupRec(readBook)
    grpRec = Hash.new
    readSheet = readBook.worksheet('Data')
    (@group.keys).each do |row|
      item = Hash.new
      grpRec[@group[row]] = item
      (@rec.keys).each_with_index do |key, offset|
        column = @group_column + offset
        tmp = nil
        @mtx.synchronize do
          tmp = readSheet[row, column]
        end
        if nil != tmp then
          item[key] = tmp
        end
      end
    end
    return grpRec
  end

  # read data sheet
  def read(readName)
    readBook = Spreadsheet.open(readName)
    th1 = Thread.new do
      readParameter(readBook)
    end
    th2 = Thread.new do
      readRecord(readBook)
    end
    th1.join
    th2.join
    th1 = Thread.new do
      @recParam = readRecordParam(readBook)
    end
    th2 = Thread.new do
      @grpRecord = readGroupRec(readBook)
    end
    th1.join
    th2.join
  end
  def getFloat()
    return @param_float
  end
  def getUInt32()
    return @param_uint32
  end
  def getInt32()
    return @param_int32
  end
  def getUInt16()
    return @param_uint16
  end
  def getInt16()
    return @param_int16
  end
  def getUInt8()
    return @param_uint8
  end
  def getInt8()
    return @param_int8
  end
  def getParam()
    obj = Hash.new
    obj["uint32"] = @param_uint32
    obj["int32"]  = @param_int32
    obj["float"]  = @param_float
    obj["uint16"] = @param_uint16
    obj["int16"]  = @param_int16
    obj["uint8"]  = @param_uint8
    obj["int8"]   = @param_int8
    return obj
  end
  def getPramList()
    result = Hash.new
    param = getParam()
    (param.keys).each do |type|
      list = param[type]
      (list.keys).each do |key|
        result[key] = list[key]
      end
    end
    return result;
  end
  def getPramTypes()
    result = Hash.new
    param = getParam()
    (param.keys).each do |type|
      list = param[type]
      (list.keys).each do |key|
        result[list[key]] = type
      end
    end
    return result;
  end
  def getRec()
    return @rec
  end
  def getRecParam()
    return @recParam
  end
  def getGroup()
    return @group
  end
  def getGrpRec()
    return @grpRecord
  end
  def getInitVal()
    return @initval
  end
  def getInitValueOfType()
    list = Hash.new
    list_val = getInitVal()
    param = getParam()
    (param.keys).each do |type|
      iparam = Hash.new()
      list[type] = iparam
      items = param[type]
      (items.keys).each do |key|
        if(list_val.key?(key)) then
          if type == "float" then
            if list_val[key] =~ /U/i then
              (list["uint32"])[key] = items[key]
              next
            end
            if list_val[key] !~ /F/i then
              (list["int32"])[key] = items[key]
              next
            end
          end
          iparam[key] = items[key]
        end
      end
    end
    return list
  end

  def getAlias()
    return @alias
  end
  def getParamStr()
    return @p_str
  end
  def listRecCount()
    rec = getRecParam()
    ptype = getPramTypes()
    (rec.keys).each_with_index do |name, idx|
      param = rec[name]
      uint32_cnt = int32_cnt = float_cnt = uint16_cnt = int16_cnt = uint8_cnt = int8_cnt = 0
      (param.keys).each do |key|
        case ptype[param[key]]
        when "uint32" then
          uint32_cnt += 1
        when "int32" then
          int32_cnt += 1
        when "float" then
          float_cnt += 1
        when "uint16" then
          uint16_cnt += 1
        when "int16" then
          int16_cnt += 1
        when "uint8" then
          uint8_cnt += 1
        when "int8" then
          int8_cnt += 1
        else
        end
      end
      r_size = uint32_cnt + int32_cnt + float_cnt + ((uint16_cnt + int16_cnt) / 2) + ((uint8_cnt + int8_cnt) / 4) + 1
      yield(idx, rec, name, param, r_size, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt)
    end
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  app = DataRecord.new
  app.read(ARGV.shift())
  pfloat  = app.getFloat()
  puint32 = app.getUInt32()
  pint32  = app.getInt32()
  puint16 = app.getUInt16()
  pint16  = app.getInt16()
  puint8  = app.getUInt8()
  pint8   = app.getInt8()
  rec     = app.getRec()
  param   = app.getParam()

  print "parameter list and parameter key on types\n"
  (param.keys).each do |type|
    list = param[type]
    printf("%s\n", type)
    (list.keys).each do |key|
      printf("  %3d, %s\n", key, list[key])
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "parameter and parameter key list\n"
  all = app.getPramList()
  (all.keys).each do |key|
    printf("  %3d: %s\n", key, all[key])
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "type is parameter\n"
  all_types = app.getPramTypes()
  (all_types.keys).each do |key|
    printf("  %-30s: %s\n", key, all_types[key])
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "record \n"
  (rec.keys).each do |key|
    printf("  %d: %s\n", key, rec[key])
  end
  print "parameter in record\n"
  rec = app.getRecParam()
  (rec.keys).each do |name|
    print '  ', name, "\n"
    param = rec[name]
    (param.keys).each do |no|
      printf("    %3d: %-8s %s\n", no, all_types[param[no]], param[no])
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "sort parameter in record\n"
  rec = app.getRecParam()
  (rec.keys).each do |name|
    print '  ', name, "\n"
    param = rec[name]
    ((param.keys).sort).each do |no|
      printf("    %3d: %-8s %s\n", no, all_types[param[no]], param[no])
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "Group \n"
  grp = app.getGroup()
  (grp.keys).each do |row|
    printf("  %3d: %s\n", row, grp[row])
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "Record in Group \n"
  grpRec = app.getGrpRec()
  rec    = app.getRec()
  (grpRec.keys).each do |name|
    print name, "\n"
    list = grpRec[name]
    (list.keys).each do |rec_key|
      printf("  %3d: %s, %s\n", rec_key, list[rec_key], rec[rec_key])
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "initilize valiable list\n"
  list_val = app.getInitVal()
  iparam = app.getInitValueOfType()
  (iparam.keys).each do |type|
    param = iparam[type]
    print "  ", type, "\n"
    (param.keys).each do |row|
      if(list_val.key?(row)) then
        printf("    %3d: %-40s : %s\n", row, param[row], list_val[row])
      end
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "alias list\n"
  list_alias= app.getAlias()
  param = app.getPramList()
  (param.keys).each do |row|
    if(list_alias.key?(row))
      printf("  %3d: %-30s : %s\n", row, param[row], list_alias[row])
    end
  end
  print "\n"

  print "-------------------------------------------------------------------------------------------\n"
  print "parameter string list\n"
  pstr= app.getParamStr()
  param = app.getPramList()
  (param.keys).each do |row|
    if(pstr.key?(row))
      printf("  %3d: %-30s : %s\n", row, param[row], pstr[row])
    end
  end
end
