#! /usr/bin/ruby

=begin rdoc
先頭のコメント部分はファイルの説明として扱う。
=end

require 'DataRecord.rb'

# DaraRecord の Alias テーブル出力クラス
class DataRecordCHeader < DataRecord
  # コンストラクタ
  def initialize()
    super()
  end
  # 中間ソースコードの生成
  def printToAlias()
    list_alias= getAlias()
    param = getPramList()
    (param.keys).each do |row|
      if(list_alias.key?(row))
        print '    printf("%5d,'
        printf("%s", param[row])
        print ':%5d,'
        printf("%s", list_alias[row])
        print '\n"'
        printf(", %s, %s);\n", param[row], list_alias[row])
      end
    end
  end
  # テーブル生成
  def pintSplit()
    hparam  = Array.new
    halias  = Array.new
    toAlias = Hash.new
    toParam = Hash.new
    STDIN.each do |str|
      str.chop!()
      arry = str.split(/:/)
      hparam.push(arry[0])
      halias.push(arry[1])
      str.gsub!(/^[^,]*,/, '')
      str.gsub!(/:[^,]*,/, ':')
      arry = str.split(/:/)
      toAlias[arry[0]] = arry[1]
      toParam[arry[1]] = arry[0]
    end
    print '#include <stdlib.h>', "\n"
    printf("const size_t %skeyParam[%d] =\n", @prefix, hparam.length)
    print "{\n"
    (hparam.sort).each_with_index do |item, idx|
      arry = item.split(/,/)
      if idx != (hparam.length - 1)
        printf("    %s, /* %3d: %-40s */\n", sprintf("%-40s", arry[1]), idx, toAlias[arry[1]])
      else
        printf("    %s  /* %3d: %-40s */\n", sprintf("%-40s", arry[1]), idx, toAlias[arry[1]])
      end
    end
    print "};\n"
    printf("const size_t %stoAlias[%d] =\n", @prefix, hparam.length)
    print "{\n"
    (hparam.sort).each_with_index do |item, idx|
      arry = item.split(/,/)
      if idx != (hparam.length - 1)
        printf("    %s, /* %3d: %-40s */\n", sprintf("%-40s", toAlias[arry[1]]), idx, arry[1])
      else
        printf("    %s  /* %3d: %-40s */\n", sprintf("%-40s", toAlias[arry[1]]), idx, arry[1])
      end
    end
    print "};\n"

    printf("const size_t %skeyAlias[%d] =\n", @prefix, halias.length)
    print "{\n"
    (halias.sort).each_with_index do |item, idx|
      arry = item.split(/,/)
      if idx != (hparam.length - 1)
        printf("    %s, /* %3d: %-40s */\n", sprintf("%-40s", arry[1]), idx, toParam[arry[1]])
      else
        printf("    %s  /* %3d: %-40s */\n", sprintf("%-40s", arry[1]), idx, toParam[arry[1]])
      end
    end
    print "};\n"
    printf("const size_t %stoParam[%d] =\n", @prefix, halias.length)
    print "{\n"
    (halias.sort).each_with_index do |item, idx|
      arry = item.split(/,/)
      if idx != (hparam.length - 1)
        printf("    %s, /* %3d: %-40s */\n", sprintf("%-40s", toParam[arry[1]]), idx, arry[1])
      else
        printf("    %s  /* %3d: %-40s */\n", sprintf("%-40s", toParam[arry[1]]), idx, arry[1])
      end
    end
    print "};\n"
  end
end

if $0 == __FILE__ then
  app = DataRecordCHeader.new
  case ARGV.shift()
  when 'make' then
    if !File.exists?(ARGV[0]) then
      print "File Not Found!"
      exit -1
    end
    app.read(ARGV.shift())
    app.opt(ARGV)
    print '#include <stdio.h>', "\n"
    print "\n"
    print 'int main(int argc, char * argv[])', "\n"
    print '{', "\n"
    app.printToAlias()
    print '    return 0;', "\n"
    print '}', "\n"
  when 'split' then
    app.opt(ARGV)
    app.pintSplit()
  else
    puts 'not sub command'
  end
end
