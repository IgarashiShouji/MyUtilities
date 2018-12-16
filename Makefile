TARGET=tester.exe
CFLAGS=-g -I ./ -I ./Include -pipe -O3 -march=native
CPPFLAGS=$(CFLAGS) -std=c++14

all: Documents/doxygen Objects Documents/doxygen/index.html Documents/rdoc/index.html $(TARGET)

clean:
	rm -rf $(TARGET) libUtilities.a Objects/*.[ao]

$(TARGET): test.cpp DataRecord.o libUtilities.a Objects Documents/doxygen
	g++ $(CPPFLAGS) -o $@ $< DataRecord.o -L ./ -lUtilities

Documents/doxygen/index.html: Doxyfile \
						Source/Entity.cpp Include/Entity.hpp \
						Source/MyUtilities.c Include/MyUtilities.h
	doxygen Doxyfile

Documents/rdoc/index.html: *.rb
	rdoc -oDocuments/rdoc *.rb

libUtilities.a: Objects/Entity.o Objects/MyUtilities.o
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


DataRecord.h: DataRecord.xls
	ruby DataRecord.rb --hpp > $@

DataRecord.cpp: DataRecord.xls
	ruby DataRecord.rb --cpp > $@

DataRecord.o: DataRecord.cpp DataRecord.h
	g++ $(CPPFLAGS) -c -o $@ $<
