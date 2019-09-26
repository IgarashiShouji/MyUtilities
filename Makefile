TARGET=tester.exe
CFLAGS=-g -I ./ -I ./Include -pipe -O3 -march=native
CPPFLAGS=$(CFLAGS) -std=c++14

all: Objects $(TARGET)

document: Documents/doxygen Documents/doxygen/index.html Documents/rdoc/index.html

clean:
	rm -rf $(TARGET) libUtilities.a Objects/*.[ao] ./*.o ./DataRec*.[ech]*

$(TARGET): test.cpp DataRecord.o DataRecordRedef.o libUtilities.a Objects Documents/doxygen
	g++ $(CPPFLAGS) -o $@ $< DataRecord.o -L ./ -lUtilities

Documents/doxygen/index.html: Doxyfile Doxyfile.msys \
						Source/Entity.cpp Include/Entity.hpp \
						Source/MyUtilities.c Source/MyConsole.c Include/MyUtilities.h
	bash --norc doxygen.sh

Documents/rdoc/index.html: *.rb
	rdoc -oDocuments/rdoc *.rb

libUtilities.a: Objects/Entity.o Objects/MyUtilities.o Objects/MyConsole.o
	ar rcs $@ $^

Objects:
	mkdir -p Objects

Documents/doxygen:
	mkdir -p $@

Objects/%.o: Source/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

Objects/%.o: Source/%.c
	gcc $(CFLAGS) -c -o $@ $<

Objects/Entity.o: Source/Entity.cpp Include/Entity.hpp
Objects/MyUtilities.o: Source/MyUtilities.c Include/MyUtilities.h
Objects/MyConsole.o: Source/MyConsole.c Include/MyUtilities.h


DataRecord.h: DataRecord.xls DataRecord.rb
	ruby DataRecord.rb DataRecord.xls --hpp --header=DataRecord > $@

DataRecord.cpp: DataRecord.xls DataRecord.rb
	ruby DataRecord.rb DataRecord.xls --cpp --header=DataRecord --no-string > $@

DataRecord.o: DataRecord.cpp DataRecord.h
	g++ $(CPPFLAGS) -c -o $@ $<

DataRecordRedefMake.cpp: DataRecord.xls ReDefine.h
	ruby DataRecord.rb DataRecord.xls --ReDefCode=ReDefine.h > $@

DataRecordRedef.exe: DataRecordRedefMake.cpp ReDefine.h
	g++ $(CPPFLAGS) -o $@ $<

DataRecordRedef.c: DataRecord.xls DataRecordRedef.exe
	echo '#include "ReDefine.h"'   >  $@
	echo '#include "DataRecord.h"' >> $@
	ruby DataRecord.rb DataRecord.xls --redefine='./DataRecordRedef.exe' | sed -e 's/\r//g' >> $@

DataRecordRedef.o: DataRecordRedef.c
	g++ $(CPPFLAGS) -c -o $@ $<
