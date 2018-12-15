TARGET=tester.exe
CFLAGS=-g -I ./ -I ./Include -pipe -O3 -march=native
CPPFLAGS=$(CFLAGS) -std=c++14

all: Doxygen Objects Doxygen/html/index.html $(TARGET)

clean:
	rm -rf $(TARGET) libUtilities.a Objects/*.[ao]

$(TARGET): test.cpp DataRecord.o libUtilities.a Objects Doxygen
	g++ $(CPPFLAGS) -o $@ $< DataRecord.o -L ./ -lUtilities

Doxygen/html/index.html: Source/Entity.cpp Include/Entity.hpp \
						Source/MyUtilities.c Include/MyUtilities.h
	doxygen Doxyfile

libUtilities.a: Objects/Entity.o Objects/MyUtilities.o
	ar rcs $@ $^

Objects:
	mkdir -p Objects

Doxygen:
	mkdir -p Doxygen

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
