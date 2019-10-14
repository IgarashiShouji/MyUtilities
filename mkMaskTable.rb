#! /usr/bin/ruby

class MakeMaskTable
  def initialize(list)
    @arg = Hash.new
    no = 0;
    list.each do |item|
      @arg[no] = item;
      no += 1
    end
  end
  def get(list)
    no = 0
    src = Array.new
    list.each do |item|
      src.push(sprintf("%d:%s", no, item))
      no += 1
    end
    out = Array.new
    no = disp(src, out, 0)
    return out
  end
  def disp(list, out, no)
    if(1 < list.length)
      list_true = Array.new
      list_false = Array.new
      str = sprintf("0xff, %4d:", no)
      for idx in 0..(list.length-1)
        str += list[idx].gsub(/^.*:/, '')
        if((idx + 1) < list.length)
          str += "|"
        end
        if(idx < (list.length/2))
          list_true.push(list[idx])
        else
          list_false.push(list[idx])
        end
      end
      out.push(str)
      idx = no
      no = disp(list_true, out, no + 1)
      out[idx] = sprintf("%4d, %4d, %s", no, idx+1, out[idx])
      no = disp(list_false, out, no)
    else
      if(1 == list.length)
        temp = list[0].split(/:/)
        str = sprintf("0xff, 0xff, %4d, %4d:%s", temp[0], no, temp[1])
        out.push(str)
        no += 1
      end
    end
    return no
  end
end

if $0 == __FILE__ then
  obj = MakeMaskTable.new(ARGV)
  out = obj.get(ARGV)

  no = 0
  printf("_mask[%d]  =  { ", out.length)
  out.each do |item|
    tmp = item.split(/:/)
    print tmp[1]
    no += 1
    if(no < out.length)
      print ", "
    end
  end
  print " };\n"

  no = 0
  printf("_no[%d]    =  { ", out.length)
  out.each do |item|
    tmp = item.split(/:/)
    tmp = tmp[0].split(/,/)
    printf("%4s", tmp[2].gsub(/^ */, ''))
    no += 1
    if(no < out.length)
      print ", "
    end
  end
  print " };\n"

  no = 0
  printf("_true[%d]  =  { ", out.length)
  out.each do |item|
    tmp = item.split(/:/)
    tmp = tmp[0].split(/,/)
    printf("%4s", tmp[1].gsub(/^ */, ''))
    no += 1
    if(no < out.length)
      print ", "
    end
  end
  print " };\n"

  no = 0
  printf("_false[%d] =  { ", out.length)
  out.each do |item|
    tmp = item.split(/:/)
    tmp = tmp[0].split(/,/)
    printf("%4s", tmp[0].gsub(/^ */, ''))
    no += 1
    if(no < out.length)
      print ", "
    end
  end
  print " };\n"
end
