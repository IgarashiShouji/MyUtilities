#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require 'DataRecord.rb'


class DataRecordCHeader < DataRecord
  def initialize()
    super()
  end
  def printList(list, name)
    printf("enum %s%s\n", @prefix, name)
    print "{", "\n"
    (list.keys).each_with_index do |key, idx|
      if(idx < (list.length - 1))
        printf("    %s,\n", list[key])
      else
        printf("    %s\n", list[key])
      end
      if((idx % @enum_max) == (@enum_max - 1))
        printf("    enum_next_%s%s%d\n", @prefix, name, (idx / @enum_max))
        print "};\n"
        printf("enum %s%s%d\n", @prefix, name, (idx / @enum_max))
        print "{", "\n"
        printf("    %s%s_prev_%d=%s,\n", @prefix, name, (idx / @enum_max), list[key])
      end
    end
    print "};\n"
  end
  def printRecCount(name)
    printf("enum %s%s\n", @prefix, name)
    print "{", "\n"
    listRecCount() do |idx, rec, name, param, r_size, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt|
      if(idx < (rec.length - 1))
        str = sprintf("RCNT_%s=(%d),", name, r_size)
      else
        str = sprintf("RCNT_%s=(%d)", name, r_size)
      end
      printf("    %-40s/* %-30s: %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d */\n", str, name, param.length, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt)
      if((idx % @enum_max) == (@enum_max - 1))
#        printf("    enum_next_%s%s%d\n", @prefix, name, (idx / @enum_max))
        print "};\n"
        printf("enum %s%s%d\n", @prefix, name, (idx / @enum_max))
        print "{", "\n"
#        printf("    %s%s_prev_%d=%s,\n", @prefix, name, (idx / @enum_max), list[key])
      end
    end
    print "};\n"
  end
  def printGrpCount(name)
    grp = getGrpRec()
    rec = getRec()
    printf("enum %sGroupRecInfo\n{\n", @prefix)
    (grp.keys).each_with_index do |gname, idx|
      list = Hash.new
      items = grp[gname]
      items.keys.each do |key|
        list[rec[key]] = gname;
      end
      max = 0
      listRecCount() do |idx, rec, rname, param, r_size, uint32_cnt, int32_cnt, float_cnt, uint16_cnt, int16_cnt, uint8_cnt, int8_cnt|
        if max < r_size then
          if(list.key?(rname)) then
            max = r_size
          end
        end
      end
      if (idx < (grp.length - 1)) then
        printf("    RCNT_%s_max=(%d),\n", gname, max)
      else
        printf("    RCNT_%s_max=(%d)\n", gname, max)
      end
    end
    printf("};\n")
  end
  def printParamCount(param, rec, grp)
    printf("enum %sparam_count\n", @prefix)
    print "{", "\n"
    printf("    %suint32_cnt=(%d),\n", @prefix, (getUInt32()).length)
    printf("    %sint32_cnt=(%d),\n", @prefix,  (getInt32()).length)
    printf("    %sfloat_cnt=(%d),\n", @prefix,  (getFloat()).length)
    printf("    %suint16_cnt=(%d),\n", @prefix, (getUInt16()).length)
    printf("    %sint16_cnt=(%d),\n", @prefix,  (getInt16()).length)
    printf("    %suint8_cnt=(%d),\n", @prefix,  (getUInt8()).length)
    printf("    %sint8_cnt=(%d),\n", @prefix,   (getInt8()).length)
    printf("    %sDWord_cnt=(%d),\n", @prefix,  ((getUInt32()).length + (getInt32()).length + (getFloat()).length))
    printf("    %sWord_cnt=(%d),\n", @prefix,   ((getUInt16()).length + (getInt16()).length))
    printf("    %sByte_cnt=(%d),\n", @prefix,   ((getUInt8()).length  + (getInt8()).length))
    printf("    %sparam_cnt=(%d),\n", @prefix,  param.length)
    printf("    %srec_cnt=(%d),\n", @prefix,    rec.length)
    printf("    %sgroup_cnt=(%d)\n", @prefix,   grp.length)
    print "};\n"
  end
  def printExternRecoard()
    rec = getRecParam()
    (rec.keys).each do |name|
      param = rec[name]
      printf("extern const size_t %s tbl_rec_%s[%d];\n", @attr, name, param.length)
    end
    (rec.keys).each do |name|
      param = rec[name]
      printf("extern const size_t %s tbl_fmt_rec_%s[%d];\n", @attr, name, param.length)
    end
  end
  def printExternGroup()
    rec = getRec()
    grp = getGrpRec()
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t %s grp_%s[%d];\n", @attr, name, list.length)
    end
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t %s grp_fmt_%s[%d];\n", @attr, name, list.length)
    end
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t %s grp_no_%s[%d];\n", @attr, name, list.length)
    end
  end
  def printExternTable(param, rec, grp)
    iparam = getInitValueOfType()
    if (0 < (iparam["uint32"]).length) then
      printf("extern const size_t %s %stbl_uint32_list[%d];\n", @attr, @prefix, (iparam["uint32"]).length)
      print "#if __x86_64__", "\n"
      printf("extern const unsigned int %s %stbl_uint32[%d];\n", @arrt, @prefix, (iparam["uint32"]).length)
      print "#else", "\n"
      printf("extern const unsigned long %s %stbl_uint32[%d];\n", @attr, @prefix, (iparam["uint32"]).length)
      print "#endif", "\n"
    end
    if (0 < (iparam["int32"]).length) then
      printf("extern const size_t %s %stbl_int32_list[%d];\n", @attr, @prefix, (iparam["int32"]).length)
      print "#if __x86_64__", "\n"
      printf("extern const signed int %s %stbl_int32[%d];\n",  @attr, @prefix, (iparam["int32"]).length)
      print "#else", "\n"
      printf("extern const signed long %s %stbl_int32[%d];\n", @attr, @prefix, (iparam["int32"]).length)
      print "#endif", "\n"
    end
    if (0 < (iparam["float"]).length) then
      printf("extern const size_t %s %stbl_float_list[%d];\n", @attr, @prefix, (iparam["float"]).length)
      printf("extern const float %s %stbl_float[%d];\n", @attr, @prefix, (iparam["float"]).length)
    end
    if (0 < (iparam["uint16"]).length) then
      printf("extern const size_t %s %stbl_uint16_list[%d];\n", @attr, @prefix, (iparam["uint16"]).length)
      printf("extern const unsigned short %s %stbl_uint16[%d];\n", @attr, @prefix, (iparam["uint16"]).length)
    end
    if (0 < (iparam["int16"]).length) then
      printf("extern const signed short %s %stbl_int16[%d];\n", @attr, @prefix, (iparam["int16"]).length)
      printf("extern const size_t %s %stbl_int16_list[%d];\n",  @attr, @prefix, (iparam["int16"]).length)
    end
    if (0 < (iparam["uint8"]).length) then
      printf("extern const unsigned char %s %stbl_uint8[%d];\n", @attr, @prefix, (iparam["uint8"]).length)
      printf("extern const size_t %s %stbl_uint8_list[%d];\n", @attr, @prefix, (iparam["uint8"]).length)
    end
    if (0 < (iparam["int8"]).length) then
      printf("extern const size_t %s %stbl_int8_list[%d];\n", @attr, @prefix, (iparam["int8"]).length)
      printf("extern const signed char %s %stbl_int8[%d];\n", @attr, @prefix, (iparam["int8"]).length)
    end

    printf("extern const size_t * const %s %stblRecIDs[%d];\n", @attr, @prefix, rec.length)
    printf("extern const size_t * const %s %stblRecFmt[%d];\n", @attr, @prefix, rec.length)
    printf("extern const size_t %s %stblRecSize[%d][8];\n", @attr, @prefix, rec.length)

    printf("extern const size_t * const %s %stblGrpIDs[%d];\n", @attr, @prefix, grp.length)
    printf("extern const size_t * const %s %stblGrpFmt[%d];\n", @attr, @prefix, grp.length)
    printf("extern const size_t * const %s %stblGrpNo[%d];\n", @attr, @prefix, grp.length)
    printf("extern const size_t %s %stblGrpSize[%d];\n", @attr, @prefix, grp.length)

    list_alias= getAlias()
    printf("extern const size_t %s %skeyParam[%d];\n", @attr, @prefix, list_alias.length)
    printf("extern const size_t %s %stoAlias[%d];\n",  @attr, @prefix, list_alias.length)
    printf("extern const size_t %s %skeyAlias[%d];\n", @attr, @prefix, list_alias.length)
    printf("extern const size_t %s %stoParam[%d];\n",  @attr, @prefix, list_alias.length)
  end
  def printStruct()
    if @no_struct then
      return
    end
    rec = getRecParam()
    all_types = getPramTypes()
    (rec.keys).each do |name|
      print "typedef struct\n{\n"
      param = rec[name]
      (param.keys).each do |no|
        case all_types[param[no]]
        when "uint32"
          print '#if __x86_64__', "\n"
          printf("    %-15s %s;\n", "unsigned int",   param[no])
          print '#else', "\n"
          printf("    %-15s %s;\n", "unsigned long",  param[no])
          print '#endif', "\n"
        when "int32"
          printf("    %-15s %s;\n", "signed long",    param[no])
        when "uint16"
          printf("    %-15s %s;\n", "unsigned short", param[no])
        when "float"
          printf("    %-15s %s;\n", "float",          param[no])
        when "int16"
          printf("    %-15s %s;\n", "signed short",   param[no])
        when "uint8"
          printf("    %-15s %s;\n", "unsigned char",  param[no])
        when "int8"
          printf("    %-15s %s;\n", "signed char",    param[no])
        else
          printf("    %-15s ", all_types[param[no]])
        end
      end
      printf("} %sstruct_%s;\n", @prefix, name)
    end
    print "typedef union\n{\n"
    (rec.keys).each do |name|
      printf("    %-39s %s;\n", sprintf("%sstruct_%s", @prefix, name), name)
    end
    printf("} %sunion_DataRecs;\n", @prefix)
    printf("extern const size_t %s %stbl_rec_offset[%d][2];\n", @attr, @prefix, rec.length)
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  app = DataRecordCHeader.new
  app.read(ARGV.shift())
  app.opt(ARGV)

  param = app.getPramList()
  rec   = app.getRec()
  grp   = app.getGroup()
  app.printList(param, "param_list")
  app.printList(rec,   "recoard_list")
  app.printList(grp,   "group_list")
  app.printRecCount("recoard_count")
  app.printGrpCount("group_count")
  app.printParamCount(param, rec, grp)
  app.printExternRecoard()
  app.printExternGroup()
  app.printExternTable(param, rec, grp)
  app.printStruct()
end
