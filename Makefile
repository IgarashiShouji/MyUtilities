TARGET=tester.exe
CFLAGS=-g -std=c++14 -I ./Include -pipe -O3 -march=native

all: Doxygen Objects Doxygen/html/index.html $(TARGET)

clean:
	rm -rf $(TARGET) libUtilities.a Objects/*.[ao]

$(TARGET): test.cpp libUtilities.a Objects Doxygen
	g++ $(CFLAGS) -o $@ $< -L ./ -lUtilities

Doxygen/html/index.html: Source/Entity.cpp Include/Entity.hpp
	doxygen Doxyfile

libUtilities.a: Objects/Entity.o
	ar rcs $@ $^

Objects:
	mkdir -p Objects

Doxygen:
	mkdir -p Doxygen

Objects/%.o: Source/%.cpp
	g++ $(CFLAGS) -c -o $@ $<

Objects/Entity.o: Source/Entity.cpp Include/Entity.hpp
