#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s21_grep {
    bool e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
    char **pattern;
    int len;
    int files_len;
    regex_t *regex;
} data;

int parser(data *info, char **args);
int len_of_search_strings(char **args, data *info, bool *first_occurance);
int search_string(data *info);
void read_files(data info, char **files, int lenfiles);
void print_file(FILE *file, data info, char *filename);
int find_match(data info, char *line);
void free_dat_shit(data info);
#endif  // SRC_GREP_S21_GREP_H_
