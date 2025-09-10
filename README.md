# My Utilities C/C++

This is embedded  utilities for C/C++.<br>
Detail is see document of doxygen.

## Basic Design

* File Dependence

![sample][1]

* Class list

| <center>Class Name</center> | <center>Description</center> |
|:---|:---|
| template<typename T> class ConstArray                  | adapter class of array of const attribute. |
| template<typename T1, typename T2> class ConstArrayMap | mapping of const array and array |
| template<typename T> class ConstArrayR                 | adapter class of reverse array of const attribute |
| template<typename T> class Compere                     | interface class of compare |
| class ConstCString : public Compere<const char *>      | C string adapter of const attribute |
| class CalcCRC16                                        | Calculate of crc16 |
| class DataRecord                                       | Data Item continar |
| class DataRecordStream                                 | data stream on data record |

* C libiraris list

| <center>Function Name</center> | <center>Description</center> |
|:---|:---|
| getIndexArrayByte    | |
| getIndexArrayWord    | |
| getIndexArrayDWord   | |
| getIndexArrayCString | |
| getRangeOfListByte   | |
| copyBitByte          | |
| copyBitWord          | |
| copyBitDWord         | |
| copyByte             | |
| copyWord             | |
| copyDWord            | |
| SimpleAlloc_init     | |
| SimpleAlloc_new      | |
| RecCtrl_init         | |
| RecCtrl_dataSize     | |
| RecCtrl_copy         | |
| RecCtrl_get          | |

## Build

* Linux
~~~
 # make all
~~~

* MSYS2
~~~
 # make all
~~~

* AVR

* ARM (cortex m)

* 78K0R

## Environments

* doxygen
* plant uml
* gem
~~~
 # gem install spreadsheet
~~~

## test application

### bin2format

This application convert binary data in the format specified by the format.

- build script

~~~bash
export CPP=g++
export LIBS=-lboost_program_options
export WSL=`cat /proc/version | grep WSL`
if [ "" !=  "${WSL}" ]; then
  export CPP=/opt/mxe/usr/bin/x86_64-w64-mingw32.static-g++
  export LIBS=-lboost_program_options-mt-x64
fi
${CPP} -g -std=c++17 -Os -o bin2format.exe bin2format.cpp -I . ${LIBS} &
~~~

- Command help.

~~~
Binary to Format value converter: Revision 0.08.02
bin2format.exe [Options] arg:
  -f [ --file ] arg       input file name
  -b [ --binary ] arg     input binary file name
  -g [ --grep ] arg       Pre-execute Grep    ex) --grep 'Regexp'
  -r [ --replace ] arg    Pre-execute Replace ex) --replace 'Regexp/Replace'
  -a [ --print-address ]  print address
  -d [ --dump ]           print binary dump
  --print-grep            print grep result
  --print-replace         print replace result
  -v [ --version ]        Print version
  -h [ --help ]           help

Usag:
  # ./bin2format.exe --file modbus.log --grep '^[RT]x:.*-..' --replace '^[RT]x:.*-(..)/$1' '^010400:bbWWH2' '^01044C:bbbVVFWDH2'
  # echo '00010102' | ./bin2format.exe '^.:WH2'  -> 1, 0102
  # echo '00010102' | ./bin2format.exe '^.:wh2'  -> 256, 0201

  # ./bin2format.exe -a -b bin2format.exe '0:h16'          -> 00000000h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '0000h:h16'      -> 00000000h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '0000h:h16:4'    -> 00000000h: xx... 
                                                              00000010h: xx... 
                                                                  ... 
                                                              00000030h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '00.0h:h16'      -> 00000000h: xx... 
                                                              00000010h: xx... 
                                                                  ... 
                                                              000000F0h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '00[01]0h:h16'   -> 00000000h: xx... 
                                                              00000010h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '00[0-4]0h:h16'  -> 00000000h: xx... 
                                                              00000010h: xx... 
                                                                  ... 
                                                              00000040h: xx... 
  # ./bin2format.exe -a -b bin2format.exe '10{3}h:h16'     -> 00001000h: xx... 

Format
    c :  8 bit signed value  
    b :  8 bit unsigned value
    s : 16 bit signed value  
    w : 16 bit unsigned value
    i : 32 bit signed value  
    d : 32 bit unsigned value
    j : 64 bit signed value  
    q : 64 bit unsigned value
    f : float                
    v : double               
    a*: ascii data          ex) 313233 -> a3 -> '123'   
    h*: hex data            ex) 313233 -> h3 -> '313233'

    cbswidjqfvah: little endien  0001 -> w -> 256
      SWIDJQFVAH: Big endien     0001 -> W ->  1
~~~

[1]:Documents/sample.svg
