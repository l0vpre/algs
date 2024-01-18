default: main
CXX = c++
CFLAGS = -Wall -Wextra -pedantic -Werror
TEST_INCLUDES = -I "../valgs"

VALGS_FILES = valgs/DoublyLinkedList.hpp \
				valgs/HashDictionary.hpp   \
				valgs/HashSet.hpp          \
				valgs/HashTable.hpp        \
				valgs/LinkedList.hpp       \
				valgs/hashes.h             \
				valgs/array_sorts.cpp      \
				valgs/linkedlist_sorts.cpp

.PHONY: clean
.PHONY: test

test.out: tests/test.cpp $(VALGS_FILES)
	@echo "Building C++ tests."
	@$(CXX) tests/test.cpp -g $(CFLAGS) $(TEST_INCLUDES) -o test.out

test: test.out
	@echo "Running C++ tests."
	@echo ""
	@./test.out

clean:
	@echo "Cleaning project directory."
	@rm -f *.out
