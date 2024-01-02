default: main

main.o: main.cpp
	g++ main.cpp -c

LinkedList.o: DoublyLinkedList.cpp
	g++ DoublyLinkedList.cpp -c

main: main.o DoublyLinkedList.o
	g++ main.o DoublyLinkedList.o -I . -o main

.PHONY:run
run: main
	./main