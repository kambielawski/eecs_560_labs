main: main.o
	g++ -g -std=c++11 -Wall main.o -o main

main.o: main.cpp Executive.h HashTable.h HashTableInterface.h
	g++ -c main.cpp

clean:
	rm -f *.o
