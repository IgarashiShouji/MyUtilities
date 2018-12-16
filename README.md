# My Utilities C/C++

This is embedded  utilities for C/C++.
<br>Detail is see document of doxygen.

## Basic Design

* File Dependence

![sample][1]

* Class list

| Class Name | Description |
|---|---|
| template<typename T> class ConstArray                  | adapter class of array of const attribute. |
| template<typename T1, typename T2> class ConstArrayMap | mapping of const array and array |
| template<typename T> class ConstArrayR                 | adapter class of reverse array of const attribute |
| template<typename T> class Compere                     | interface class of compare |
| class ConstCString : public Compere<const char *>      | C string adapter of const attribute |
| class CalcCRC16                                        | Calculate of crc16 |
| class DataRecord                                       | Data Item continar |
| class DataRecordStream                                 | data stream on data record |

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

[1]:Documents/sample.svg
