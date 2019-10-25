#! /usr/bin/ruby

class MakeMaskTable
  def initialize(list)
    @arg       = Hash.new
    @arg_no    = Hash.new
    @arg_true  = Hash.new
    @arg_false = Hash.new

    @item_no = 0
    no = 0
    stack = Array.new
    trace = Array.new
    while(0 < list.length)
      @arg[no] = Array.new(list)
      if(1 < list.length)
        @arg_no[no] = 0xff
        @arg_true[no] = no + 1
        @arg_false[no] = 0xff
        list_next = list.slice!(0, (list.length / 2))
        stack.push(list)
        trace.push(no + 1)
        list = list_next
      else
        @arg_no[no] = @item_no
        @item_no += 1
        @arg_true[no] = 0xff
        @arg_false[no] = 0xff
        if(0 < stack.length)
          list = stack.pop();
          idx  = trace.pop();
          @arg_false[idx] = no + 1
        else
          break
        end
      end
      no += 1
    end
  end
  def list()
    return @arg
  end
  def no()
    return @arg_no
  end
  def true_list()
    return @arg_true
  end
  def false_list()
    return @arg_false
  end
  def maxCount()
    return @item_no
  end
end

if $0 == __FILE__ then
  app = MakeMaskTable.new(ARGV)
  list       = app.list()
  list_no    = app.no()
  list_true  = app.true_list()
  list_false = app.false_list()
  print "idx, no, true, false, list", "\n"
  list.keys.each do |key|
    printf("%2d, %02x, ", key, list_no[key])
    if(list_true[key] < list.length)
      printf("%2d, ",  list_true[key])
    else
      printf("%02x, ", list_true[key])
    end
    if(list_false[key] < list.length)
      printf("%2d: ",  list_false[key])
    else
      printf("%02x: ", list_false[key])
    end
    print list[key], "\n"
  end
end
