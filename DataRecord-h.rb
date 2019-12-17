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
        printf("    enum_next_%s%s%d\n", pprefix, name, (idx / @enum_max))
        print "};\n"
        printf("enum %s%s%d\n", pprefix, name, (idx / @enum_max))
        print "{", "\n"
        printf("    %s%s_prev_%d=%s,\n", @prefix, name, (idx / @enum_max), list[key])
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
      printf("extern const size_t tbl_rec_%s[%d];\n", name, param.length)
    end
    (rec.keys).each do |name|
      param = rec[name]
      printf("extern const size_t tbl_fmt_rec_%s[%d];\n", name, param.length)
    end
  end
  def printExternGroup()
    rec = getRec()
    grp = getGrpRec()
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t grp_%s[%d];\n", name, list.length)
    end
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t grp_fmt_%s[%d];\n", name, list.length)
    end
    (grp.keys).each do |name|
      list = grp[name]
      printf("extern const size_t grp_no_%s[%d];\n", name, list.length)
    end
  end
  def printExternTable(param, rec, grp)
    iparam = getInitValueOfType()
    if (0 < (iparam["uint32"]).length) then
      printf("extern const size_t %stbl_uint32_list[%d];\n",   @prefix, (iparam["uint32"]).length)
      print "#if __x86_64__", "\n"
      printf("extern const unsigned int %stbl_uint32[%d];\n",  @prefix, (iparam["uint32"]).length)
      print "#else", "\n"
      printf("extern const unsigned long %stbl_uint32[%d];\n", @prefix, (iparam["uint32"]).length)
      print "#endif", "\n"
    end
    if (0 < (iparam["int32"]).length) then
      printf("extern const size_t %stbl_int32_list[%d];\n", @prefix, (iparam["int32"]).length)
      print "#if __x86_64__", "\n"
      printf("extern const signed int %stbl_int32[%d];\n",  @prefix, (iparam["int32"]).length)
      print "#else", "\n"
      printf("extern const signed long %stbl_int32[%d];\n", @prefix, (iparam["int32"]).length)
      print "#endif", "\n"
    end
    if (0 < (iparam["float"]).length) then
      printf("extern const size_t %stbl_float_list[%d];\n", @prefix, (iparam["float"]).length)
      printf("extern const float %stbl_float[%d];\n",       @prefix, (iparam["float"]).length)
    end
    if (0 < (iparam["uint16"]).length) then
      printf("extern const size_t %stbl_uint16_list[%d];\n",    @prefix, (iparam["uint16"]).length)
      printf("extern const unsigned short %stbl_uint16[%d];\n", @prefix, (iparam["uint16"]).length)
    end
    if (0 < (iparam["int16"]).length) then
      printf("extern const signed short %stbl_int16[%d];\n", @prefix, (iparam["int16"]).length)
      printf("extern const size_t %stbl_int16_list[%d];\n",  @prefix, (iparam["int16"]).length)
    end
    if (0 < (iparam["uint8"]).length) then
      printf("extern const unsigned char %stbl_uint8[%d];\n", @prefix, (iparam["uint8"]).length)
      printf("extern const size_t %stbl_uint8_list[%d];\n",   @prefix, (iparam["uint8"]).length)
    end
    if (0 < (iparam["int8"]).length) then
      printf("extern const size_t %stbl_int8_list[%d];\n", @prefix, (iparam["int8"]).length)
      printf("extern const signed char %stbl_int8[%d];\n", @prefix, (iparam["int8"]).length)
    end

    printf("extern const size_t * const %stblRecIDs[%d];\n", @prefix, rec.length)
    printf("extern const size_t * const %stblRecFmt[%d];\n", @prefix, rec.length)
    printf("extern const size_t %stblRecSize[%d][8];\n",     @prefix, rec.length)

    printf("extern const size_t * const %stblGrpIDs[%d];\n", @prefix, grp.length)
    printf("extern const size_t * const %stblGrpFmt[%d];\n", @prefix, grp.length)
    printf("extern const size_t * const %stblGrpNo[%d];\n", @prefix, grp.length)
    printf("extern const size_t %stblGrpSize[%d];\n",     @prefix, grp.length)

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
end
