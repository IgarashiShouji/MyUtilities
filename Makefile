TARGET=tester.exe
CFLAGS=-g -ansi --input-charset=UTF-8 --exec-charset=UTF-8 -I ./ -I ./Include -pipe -O3 -march=native
CPPFLAGS=$(CFLAGS) -std=c++17

ifdef CROSSDEV
CC=$(CROSSDEV)-gcc
CPP=$(CROSSDEV)-g++
AR=$(CROSSDEV)-ar
else
CC=gcc
CPP=g++
AR=ar
endif

all: Objects $(TARGET)

lib: Objects libUtilities.a

document: Documents/doxygen Documents/doxygen/index.html Documents/rdoc/index.html

clean:
	rm -rf $(TARGET) libUtilities.a Objects/*.[ao] ./*.o ./DataRec*.[ech]*

$(TARGET): test.cpp DataRecord.o DataRecordRedef.o libUtilities.a Objects Documents/doxygen
	$(CPP) $(CPPFLAGS) -o $@ $< DataRecord.o -L ./ -lUtilities

Documents/doxygen/index.html: Doxyfile Doxyfile.msys \
						Source/Entity.cpp Include/Entity.hpp \
						Source/MyUtilities.c Source/MyConsole.c Include/MyUtilities.h
	bash --norc doxygen.sh

Documents/rdoc/index.html: *.rb
	rdoc -oDocuments/rdoc *.rb

libUtilities.a: Objects/Entity.o Objects/MyUtilities.o Objects/MyConsole.o
	$(AR) rcs $@ $^

Objects:
	mkdir -p Objects

Documents/doxygen:
	mkdir -p $@

Objects/%.o: Source/%.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

Objects/%.o: Source/%.c
	$(CC) $(CFLAGS) -std=c99 -c -o $@ $<

Objects/Entity.o: Source/Entity.cpp Include/Entity.hpp
Objects/MyUtilities.o: Source/MyUtilities.c Include/MyUtilities.h
Objects/MyConsole.o: Source/MyConsole.c Include/MyUtilities.h

DataRecord.hpp: DataRecord.xls DataRecord.rb
	bash DataRecord.sh hpp

DataRecord.cpp: DataRecord.xls DataRecord.rb
	bash DataRecord.sh cpp

DataRecord.o: DataRecord.cpp DataRecord.hpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

DataRecordRedef.c: DataRecord.xls DataRecord.hpp
	bash DataRecord.sh alias-hpp

DataRecordRedef.o: DataRecordRedef.c
	$(CPP) $(CPPFLAGS) -c -o $@ $<
