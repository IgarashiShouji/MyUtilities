#! /usr/bin/bash

if [ -z $MSYSTEM ]; then
  doxygen Doxyfile
else
  doxygen Doxyfile.msys
fi
