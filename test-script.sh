#! /bin/bash --norc

case "$1" in
  "h")
    {
      echo '#ifndef _DataRecord_h_'
      echo '#define _DataRecord_h_'
      echo ''
      ./DataRecord-h.rb DataRecord.xls
      echo ''
      echo ''
      echo '#endif'
    } > DataRecord.h
    ;;
  "hpp")
    {
      echo '#ifndef _DataRecord_hpp_'
      echo '#define _DataRecord_hpp_'
      echo ''
      echo '#include <cstdlib>'
      echo ''
      ./DataRecord-h.rb DataRecord.xls
      echo ''
      echo ''
      echo '#endif'
    } > DataRecord.hpp
    ;;
  "c")
    {
      echo '#include "DataRecord.h"'
      ./DataRecord-c.rb DataRecord.xls
    } > DataRecord.c
    ;;
  "cpp")
    {
      echo '#include "DataRecord.hpp"'
      ./DataRecord-c.rb DataRecord.xls
    } > DataRecord.cpp
    ;;
  "alias-hpp")
    {
      echo '#include "ReDefine.h"'
      echo '#include "DataRecord.hpp"'
      ./DataRecord-mkAlias.rb DataRecord.xls
    } > DataRecordRedefMake.cpp
    g++ -g -I ./ -I ./Include -pipe -O0 -march=native -std=c++14 -o DataRecordRedef.exe DataRecordRedefMake.cpp
    {
      echo '#include "ReDefine.h"'
      echo '#include "DataRecord.hpp"'
      ./DataRecordRedef.exe| ./DataRecord-mkAlias.rb DataRecord.xls --split
    } > DataRecordRedef.c
    ;;
  *)
    $0 hpp &
    $0 cpp &
    $0 alias-hpp &
    wait
    ;;
esac
