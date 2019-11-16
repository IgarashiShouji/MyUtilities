#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require './DataRecord.rb'


class DataRecordCTable < DataRecord
  def initialize()
    super()
  end
  def printInitValueList(pinit, list)
    printf("{\n")
    (list.keys).each_with_index do |key, idx|
      if(pinit.key?(key))
        if(idx < (list.length - 1)) then
          printf("    %s,\n", list[key])
        else
          printf("    %s\n", list[key])
        end
      else
        if(idx < (list.length - 1)) then
          printf("    %s,\n", list[key])
        else
          printf("    %s\n", list[key])
        end
      end
    end
    printf("};\n")
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
    iparam = getInitValueOfType()
    param = iparam["uint32"]
    if(0 < param.length)
      printf("const size_t %stbl_uint32_list[%d] =\n",   @prefix, param.length)
      printInitValueList(pinit, param)
      print "#if __x86_64__", "\n"
      printf("const unsigned int %stbl_uint32[%d] =\n",  @prefix, param.length)
      printInitValue(pinit, param, "unsigned int")
      print "#else", "\n"
      printf("const unsigned long %stbl_uint32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned long")
      print "#endif", "\n"
    end
    param = iparam["int32"]
    if(0 < param.length)
      printf("const size_t %stbl_int32_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      print "#if __x86_64__", "\n"
      printf("const signed int %stbl_int32[%d] =\n",  @prefix, param.length)
      printInitValue(pinit, param, "signed int")
      print "#else", "\n"
      printf("const signed long %stbl_int32[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed long")
      print "#endif", "\n"
    end
    param = iparam["float"]
    if(0 < param.length)
      printf("const size_t %stbl_float_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      printf("const float %stbl_float[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "float")
    end
    param = iparam["uint16"]
    if(0 < param.length)
      printf("const size_t %stbl_uint16_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      printf("const unsigned short %stbl_uint16[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned short")
    end
    param = iparam["int16"]
    if(0 < param.length)
      printf("const size_t %stbl_int16_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      printf("const signed short %stbl_int16[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "signed short")
    end
    param = iparam["uint8"]
    if(0 < param.length)
      printf("const size_t %stbl_uint8_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      printf("const unsigned char %stbl_uint8[%d] =\n", @prefix, param.length)
      printInitValue(pinit, param, "unsigned char")
    end
    param = iparam["int8"]
    if(0 < param.length)
      printf("const size_t %stbl_int8_list[%d] =\n", @prefix, param.length)
      printInitValueList(pinit, param)
      printf("const signed char %stbl_int8[%d] =\n", @prefix, param.length)
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
      printf("static const size_t tbl_fmt_rec_%s[%d] = {", name, param.length)
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
        printf("&(tbl_fmt_rec_%s[0]), ", name)
      else
        printf("&(tbl_fmt_rec_%s[0])", name)
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

  def printGroup()
    rec = getRec()
    grp = getGrpRec()
    (grp.keys).each do |name|
      list = grp[name]
      printf("static const size_t grp_%s[%d] =\n", name, list.length)
      print '{' "\n"
      (list.keys).each_with_index do |key, idx|
        if (idx < (list.length - 1)) then
          printf("  %s,\n", rec[key])
        else
          printf("  %s\n", rec[key])
        end
      end
      print '};' "\n"
    end
    printf("const size_t * const %stblGrpIDs[%d] = {", @prefix, grp.length)
    (grp.keys).each_with_index do |name, idx|
      if (idx < (grp.length - 1)) then
        print '&(grp_', name, "[0]), "
      else
        print '&(grp_', name, "[0])"
      end
    end
    print "};\n"
    (grp.keys).each do |name|
      list = grp[name]
      printf("static const size_t grp_fmt_%s[%d] =\n", name, list.length)
      print '{' "\n"
      fmt = Hash.new()
      (list.keys).each do |key|
        fmt[list[key]] = key
      end
      ((fmt.keys).sort).each_with_index do |key, idx|
        if (idx < (fmt.length - 1)) then
          str = sprintf("%s,", rec[fmt[key]])
        else
          str = sprintf("%s", rec[fmt[key]])
        end
        printf("  %-40s/* %4d */\n", str, key)
      end
      print '};' "\n"
    end
    printf("const size_t * const %stblGrpFmt[%d] = {", @prefix, grp.length)
    (grp.keys).each_with_index do |name, idx|
      if (idx < (grp.length - 1)) then
        print '&(grp_fmt_', name, "[0]), "
      else
        print '&(grp_fmt_', name, "[0])"
      end
    end
    print "};\n"
    (grp.keys).each do |name|
      list = grp[name]
      printf("static const size_t grp_no_%s[%d] =\n", name, list.length)
      print '{' "\n"
      fmt = Hash.new()
      (list.keys).each do |key|
        fmt[list[key]] = key
      end
      ((fmt.keys).sort).each_with_index do |key, idx|
        if (idx < (fmt.length - 1)) then
          str = sprintf("%4d,", key)
        else
          str = sprintf("%4d", key)
        end
        printf("  %-40s/* %s */\n", str, rec[fmt[key]])
      end
      print '};' "\n"
    end
    printf("const size_t * const %stblGrpNo[%d] = {", @prefix, grp.length)
    (grp.keys).each_with_index do |name, idx|
      if (idx < (grp.length - 1)) then
        print '&(grp_no_', name, "[0]), "
      else
        print '&(grp_no_', name, "[0])"
      end
    end
    print "};\n"
    printf("const size_t %stblGrpSize[%d] = {",     @prefix, grp.length)
    (grp.keys).each_with_index do |name, idx|
      if (idx < (grp.length - 1)) then
        printf("%d, ", grp[name].length)
      else
        printf("%d", grp[name].length)
      end
    end
    print "};\n"
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  app = DataRecordCTable.new
  app.read(ARGV.shift())
  app.opt(ARGV)

  app.printInitVlue()
  app.printRecoard()
  app.printGroup()
end
