ASAN:=#-fsanitize=address -g
CFLAGS= -Wall -Wextra -std=c11 #-Werror -g 

all: s21_cat

s21_cat:
	gcc $(CFLAGS) $(ASAN) s21_cat.c -o s21_cat

test: s21_cat
	chmod 777 test.py
	python3 test.py

clean:
	rm -rf s21_cat
	rm -rf *.ntesting
	rm -rf s21_cat.dSYM

re: clean all
