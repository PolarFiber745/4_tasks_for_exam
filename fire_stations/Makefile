all: output clean

output: main.o
	g++ main.o  -o a.exe

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o 