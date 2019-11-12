#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require './DataRecord.rb'


class DataRecordCTable < DataRecord
  def initialize()
    super()
  end
  def printInitValue(pinit, list, type)
    printf("{\n")
    (list.keys).each_with_index do |key, idx|
      if(pinit.key?(key))
        if(idx < (list.length - 1)) then
          printf("    %-30s /* %-30s*/\n", sprintf("(%s)(%s),", type, pinit[key]), list[key])
        else
          printf("    %-30s /* %-30s*/\n", sprintf("(%s)(%s)", type, pinit[key]), list[key])
        end
      else
        if(idx < (list.length - 1)) then
          printf("    %-30s /* %-30s*/\n", sprintf("(%s)(0),", type), list[key])
        else
          printf("    %-30s /* %-30s*/\n", sprintf("(%s)(0)", type), list[key])
        end
      end
    end
    printf("};\n")
  end
  def printInitVlue()
    pinit = getInitVal()
    param = getUInt32()
    if(0 < param.length)
      print "#if __x86_64__", "\n"
      printf("const unsigned int %stbl_init_uint32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned int")
      print "#else", "\n"
      printf("const unsigned long %stbl_init_uint32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned long")
      print "#endif", "\n"
    end
    param = getInt32()
    if(0 < param.length)
      print "#if __x86_64__", "\n"
      printf("const signed int %stbl_init_int32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed int")
      print "#else", "\n"
      printf("const signed long %stbl_init_int32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed long")
      print "#endif", "\n"
    end
    param = getFloat()
    if(0 < param.length)
      printf("const float %stbl_init_float[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "float")
    end
    param = getUInt16()
    if(0 < param.length)
      printf("const unsigned short %stbl_init_uint16[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned short")
    end
    param = getInt16()
    if(0 < param.length)
      printf("const signed short %stbl_init_int16[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed short")
    end
    param = getUInt8()
    if(0 < param.length)
      printf("const unsigned char %stbl_init_uint8[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned char")
    end
    param = getInt8()
    if(0 < param.length)
      printf("const signed char %stbl_init_int8[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed char")
    end
  end
  def printRecoard()
    rec = getRecParam()
    (rec.keys).each do |name|
      param = rec[name]
      printf("static const size_t tbl_rec_%s[%d] = {", name, param.length)
      (param.keys).each_with_index do |key, idx|
        if(idx < (param.length - 1))
          printf("%s, ", param[key])
        else
          printf("%s", param[key])
        end
      end
      print "};", "\n"
    end
    printf("const size_t * const %stblRecIDs[%d] = {", @prefix, rec.length)
    (rec.keys).each_with_index do |name, idx|
      if(idx < (rec.length - 1))
        printf("&(tbl_rec_%s[0]), ", name)
      else
        printf("&(tbl_rec_%s[0])", name)
      end
    end
    print "};", "\n"

    (rec.keys).each do |name|
      param = rec[name]
      printf("static const size_t tbl_trs_rec_%s[%d] = {", name, param.length)
      ((param.keys).sort).each_with_index do |key, idx|
        if(idx < (param.length - 1))
          printf("%s, ", param[key])
        else
          printf("%s", param[key])
        end
      end
      print "};", "\n"
    end
    printf("const size_t * const %stblRecFmt[%d] = {", @prefix, rec.length)
    (rec.keys).each_with_index do |name, idx|
      if(idx < (rec.length - 1))
        printf("&(tbl_trs_rec_%s[0]), ", name)
      else
        printf("&(tbl_trs_rec_%s[0])", name)
      end
    end
    print "};", "\n"

    printf("const size_t %stblRecSize[%d][8] = \n", @prefix, rec.length)
    print "{ /* param cnt, uint32 cnt, int32 cnt, float cnt, uint16 cnt, int16 cnt, uint8 cnt, int8 cnt */", "\n"
    listRecCount() do |idx, rec, name, param, r_size, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt|
      if(idx < (rec.length - 1))
        printf("    {%3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d},    /* %-20s */\n", param.length, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt, name)
      else
        printf("    {%3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d}     /* %-20s */\n", param.length, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt, name)
      end
    end
    print "};", "\n"
    printf("const size_t %stbl_recid[%d] = {", @prefix, rec.length)
    (rec.keys).each_with_index do |name, idx|
      if(idx < (rec.length - 1))
        printf("%s, ", name)
      else
        printf("%s", name)
      end
    end
    print "};", "\n"
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  app = DataRecordCTable.new
  app.read(ARGV.shift())

  app.printInitVlue()
  app.printRecoard()
end
