#! /bin/bash --norc

case "$1" in
  "h")
    {
      echo '#ifndef _DataRecord_h_'
      echo '#define _DataRecord_h_'
      echo ''
      ruby ./DataRecord-h.rb DataRecord.xls
      echo ''
      echo ''
      echo '#endif'
    } | ruby -ne '$_.chop!(); puts $_' > DataRecord.h
    ;;
  "hpp")
    {
      echo '#ifndef _DataRecord_hpp_'
      echo '#define _DataRecord_hpp_'
      echo ''
      echo '#include <cstdlib>'
      echo ''
      ruby ./DataRecord-h.rb DataRecord.xls
      echo ''
      echo ''
      echo '#endif'
    } | ruby -ne '$_.chop!(); puts $_' > DataRecord.hpp
    ;;
  "c")
    {
      echo '#include "DataRecord.h"'
      ruby ./DataRecord-c.rb DataRecord.xls
    } | ruby -ne '$_.chop!(); puts $_' > DataRecord.c
    ;;
  "cpp")
    {
      echo '#include "DataRecord.hpp"'
      ruby ./DataRecord-c.rb DataRecord.xls
    } | ruby -ne '$_.chop!(); puts $_' > DataRecord.cpp
    ;;
  "alias-hpp")
    {
      echo '#include "ReDefine.h"'
      echo '#include "DataRecord.hpp"'
      ruby ./DataRecord-mkAlias.rb DataRecord.xls
    } | ruby -ne '$_.chop!(); puts $_' > DataRecordRedefMake.cpp
    g++ -g -I ./ -I ./Include -pipe -O0 -march=native -std=c++14 -o DataRecordRedef.exe DataRecordRedefMake.cpp
    {
      echo '#include "ReDefine.h"'
      echo '#include "DataRecord.hpp"'
      ./DataRecordRedef.exe| ruby ./DataRecord-mkAlias.rb DataRecord.xls --split
    } | ruby -ne '$_.chop!(); puts $_' > DataRecordRedef.c
    ;;
  *)
    $0 hpp &
    $0 cpp &
    wait
    $0 alias-hpp &
    wait
    ;;
esac
