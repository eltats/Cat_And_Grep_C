#!python3

from itertools import combinations_with_replacement
from random import shuffle
from os import system

my_cat = "./s21_cat"
cat = "cat"

files = [
    'data-samples/aboba.txt',
    'data-samples/sample.txt',
    'data-samples/sample1.txt',
    'data-samples/test.txt',
    'data-samples/test1.txt',
    'data-samples/test2.txt',
    'data-samples/test3.txt'
]

testing_file = 'testing_file'
testing_file_format = ".ntesting"

flags = {
    '',
    '-b',
    '-e',
    '-n',
    '-s',
    '-v',
    '-t'}


all_var = list(combinations_with_replacement(flags, len(flags)))

def check_files(a, b):
    with open(a) as file_1:
        with open(b) as file_2:
            a, b = file_1.read(), file_2.read()
            if a != b:
                # count = 0
                # for i in range(len(a)):
                #     if a[i] == '\n':
                #         count += 1
                #     if len(b) == i:
                #         break
                #     if a[i] != b[i]:
                #         break
                input("Error. Press any key to continue:\n")

for flag in all_var:
    for fd in files:
        system(f'{my_cat} {" ".join(flag)} {"".join(fd)} > {testing_file+testing_file_format}')
        system(f'{cat} {" ".join(flag)} {"".join(fd)} > {testing_file+"_orig"+testing_file_format}')
        print(f'{my_cat} {" ".join(flag)} {"".join(fd)} > {testing_file+testing_file_format}')
        print(f'{cat} {" ".join(flag)} {"".join(fd)} > {testing_file+"_orig"+testing_file_format}')
        print()
        check_files(testing_file+testing_file_format, testing_file+"_orig"+testing_file_format)