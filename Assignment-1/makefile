CC = g++ -std=c++20

default: bin/Test-Assignment-1

bin/Test-Assignment-1: build/Assignment-1.o build/Test1.o bin
	$(CC) -o bin/Test-Assignment-1 build/Test1.o build/Assignment-1.o

build/Assignment-1.o: Assignment-1.cpp build
	$(CC) -o build/Assignment-1.o -c Assignment-1.cpp

build/Test1.o: Test1.cpp build
	$(CC) -o build/Test1.o -c Test1.cpp

build:
	mkdir build

bin:
	mkdir bin

