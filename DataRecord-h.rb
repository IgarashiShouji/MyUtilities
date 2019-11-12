#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require './DataRecord.rb'


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
        print "};\n"
        printf("enum %s%s%d\n", pprefix, name, (idx / @enum_max))
        print "{", "\n"
        printf("    %s%s_prev_%d=%s,\n", @prefix, name, (idx / @enum_max), list[key])
      end
    end
    print "};\n"
  end
  def printGrpCount(name)
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
  def printExternTable(param, rec, grp)
    if (0 < (getUInt32()).length) then
      printf("extern const size_t %stbl_uint32_list[%d];\n", @prefix, (getUInt32()).length)
      print "#if __x86_64__", "\n"
      printf("extern const unsigned int %stbl_uint32[%d];\n", @prefix, (getUInt32()).length)
      print "#else", "\n"
      printf("extern const unsigned long %stbl_uint32[%d];\n", @prefix, (getUInt32()).length)
      print "#endif", "\n"
    end
    if (0 < (getUInt32()).length) then
      printf("extern const size_t %stbl_int32_list[%d];\n", @prefix, (getInt32()).length)
      print "#if __x86_64__", "\n"
      printf("extern const signed int %stbl_int32[%d];\n", @prefix, (getInt32()).length)
      print "#else", "\n"
      printf("extern const signed long %stbl_int32[%d];\n", @prefix, (getInt32()).length)
      print "#endif", "\n"
    end
    if (0 < (getFloat()).length) then
      printf("extern const size_t %stbl_float_list[%d];\n", @prefix, (getFloat()).length)
      printf("extern const float %stbl_float[%d];\n", @prefix, (getFloat()).length)
    end
    if (0 < (getUInt16()).length) then
      printf("extern const size_t %stbl_uint16_list[%d];\n", @prefix, (getUInt16()).length)
      printf("extern const unsigned short %stbl_uint16[%d];\n", @prefix, (getUInt16()).length)
    end
    if (0 < (getInt16()).length) then
      printf("extern const signed short %stbl_int16[%d];\n", @prefix, (getInt16()).length)
      printf("extern const size_t %stbl_int16_list[%d];\n", @prefix, (getInt16()).length)
    end
    if (0 < (getUInt8()).length) then
      printf("extern const unsigned char %stbl_uint8[%d];\n", @prefix, (getUInt8()).length)
      printf("extern const size_t %stbl_uint8_list[%d];\n", @prefix, (getUInt8()).length)
    end
    if (0 < (getInt8()).length) then
      printf("extern const size_t %stbl_int8_list[%d];\n", @prefix, (getInt8()).length)
      printf("extern const signed char %stbl_int8[%d];\n", @prefix, (getInt8()).length)
    end

    printf("extern const size_t * const %stblRecIDs[%d];\n", @prefix, rec.length)
    printf("extern const size_t * const %stblRecFmt[%d];\n", @prefix, rec.length)
    printf("extern const size_t %stblRecSize[%d][8];\n", @prefix, rec.length)

    list_alias= getAlias()
    printf("extern const size_t %skeyParam[%d];\n", @prefix, list_alias.length)
    printf("extern const size_t %stoAlias[%d];\n",  @prefix, list_alias.length)
    printf("extern const size_t %skeyAlias[%d];\n", @prefix, list_alias.length)
    printf("extern const size_t %stoParam[%d];\n",  @prefix, list_alias.length)
  end
end

if $0 == __FILE__ then
  if !File.exists?(ARGV[0]) then
    print "File Not Found!"
    exit -1
  end
  app = DataRecordCHeader.new
  app.read(ARGV.shift())
  param = app.getPramList()
  rec   = app.getRec()
  grp   = app.getGroup()
  app.printList(param, "param_list")
  app.printList(rec,   "recoard_list")
  app.printList(grp,   "group_list")
  app.printRecCount("recoard_count")
  app.printGrpCount("group_count")
  app.printParamCount(param, rec, grp)
  app.printExternTable(param, rec, grp)
end
