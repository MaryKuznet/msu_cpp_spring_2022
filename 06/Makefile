CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test, clean

all: test_bin

test_bin: tests.cpp
	$(CC) $(FLAGS) tests.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o test_bin