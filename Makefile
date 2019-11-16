TARGET=tester.exe
CFLAGS=-g -I ./ -I ./Include -pipe -O0 -march=native
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

DataRecord.hpp: DataRecord.xls DataRecord.rb
	bash DataRecord.sh hpp

DataRecord.cpp: DataRecord.xls DataRecord.rb
	bash DataRecord.sh cpp

DataRecord.o: DataRecord.cpp DataRecord.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

DataRecordRedef.c: DataRecord.xls DataRecord.hpp
	bash DataRecord.sh alias-hpp

DataRecordRedef.o: DataRecordRedef.c
	g++ $(CPPFLAGS) -c -o $@ $<
