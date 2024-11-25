all: donk

donk: main.o
	g++ -g -Wall main.o -o donk.exe

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm -rf -v *.o
	rm -rf -v *.gch
