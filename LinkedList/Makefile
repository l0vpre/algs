default: main

main.o: main.cpp
	g++ main.cpp -c

LinkedList.o: LinkedList.cpp
	g++ LinkedList.cpp -c

main: main.o LinkedList.o
	g++ main.o LinkedList.o -I . -o main

.PHONY:run
run: main
	./main