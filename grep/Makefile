ASAN:=#-fsanitize=address -g
CFLAGS= -D_GNU_SOURCE -Wall -Wextra -std=c11 #-Werror -g 

all: s21_grep

s21_grep:
	gcc $(CFLAGS) s21_grep.c -o s21_grep

test: s21_grep
	chmod 777 s21_grep_tests.py
	python3 s21_grep_tests.py

clean:
	rm -rf s21_grep
	rm -rf *.res
	rm -rf s21_grep.dSYM

re: clean all