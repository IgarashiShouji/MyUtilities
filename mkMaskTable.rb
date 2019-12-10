#! /usr/bin/ruby

require "analisysMaskTable.rb"

def prnTable(mode, list, str)
  idx = 0
  printf("%-42s= {", sprintf("%s[%d]", str, list.length))
  list.keys.each_with_index do |key, idx|
    case mode
    when "list" then
      printf("/* %2d */(", key)
      (list[key]).each_with_index do |item, no|
        print item
        if(no < ((list[key]).length - 1))
          print "|"
        end
      end
      print ")"
    when "val" then
      val = list[key]
      if(val < list.length)
        printf("%4d", val)
      else
        printf("0x%02X", val)
      end
    else
    end
    if(idx < (list.length - 1))
      print ", "
    end
  end
  print "};\n"
end

if $0 == __FILE__ then
  app = MakeMaskTable.new(ARGV)
  list       = app.list()
  list_no    = app.no()
  list_true  = app.true_list()
  list_false = app.false_list()

  prnTable("list", list,        "static const unsigned short tbl_mask")
  prnTable("val",  list_true,  "static const unsigned char  tbl_true")
  prnTable("val",  list_false, "static const unsigned char  tbl_false")
  prnTable("val",  list_no,    "static const unsigned char  tbl_no")
  printf("enum {MaxCount=%d};\n", app.maxCount());
end
