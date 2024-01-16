default: main
CXX = c++
main: main.cpp
	$(CXX) main.cpp -O3 -I . -Wall -Wextra -pedantic -Werror -o main

.PHONY:run
run: main
	./main

.PHONY: clean
clean:
	rm -f main