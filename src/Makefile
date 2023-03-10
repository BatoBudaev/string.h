CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -c -g
OS := $(shell uname)
TEST_FLAGS = $(shell pkg-config --cflags --libs check) -lm

all: clean s21_string.a test gcov_report

test: test.o s21_string.a
	$(CC) test.o s21_string.a -o test -L. $(TEST_FLAGS)

test.o: test.c
	$(CC) $(CFLAGS) test.c -o test.o

s21_string.a: s21_string.o s21_sprintf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

s21_string.o: s21_string.c
	$(CC) $(CFLAGS) s21_string.c -o s21_string.o

s21_sprintf.o: s21_sprintf.c
	$(CC) $(CFLAGS) s21_sprintf.c -o s21_sprintf.o -lm

clean:
	rm -rf *.o *.a *.out *.info *.html *.gc* test gcov_report s21_string report

gcov_report:
	$(CC) -fprofile-arcs -ftest-coverage test.c s21_string.c s21_sprintf.c -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/src/index.html
else
	xdg-open report/src/index.html
endif

clang:
	clang-format -n -style=google *.c *.h

clangI:
	clang-format -i -style=google *.c *.h

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind --leak-check=full -s --track-origins=yes ./test
endif
	

rebuild: all
