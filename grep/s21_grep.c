#include "s21_grep.h"

int main(int ac, char **av) {
    data info = {};
    if (ac > 2) {
        if (parser(&info, av)) {
            if (search_string(&info)) {
                read_files(info, av, ac);
                free_dat_shit(info);
            }
        }
    } else {
        fprintf(stderr, "Not enough arguments\n");
    }
}

int parser(data *info, char **args) {
    bool first_occurance = 0;
    int counter = 0;
    int arglen = 0;
    int ret = 1;
    info->files_len = 0;
    info->len = len_of_search_strings(args, info, &first_occurance);
    info->pattern = (char **)calloc(info->len, sizeof(char *));
    if (info->pattern) {
        for (int i = 1; args[i] && ret; i++) {
            if (args[i][0] == '-') {
                for (int j = 1; args[i][j]; j++) {
                    if (args[i][j] == 'e') {
                        first_occurance = false;
                    } else if (args[i][j] == 'i') {
                        info->i = true;
                    } else if (args[i][j] == 'v') {
                        info->v = true;
                    } else if (args[i][j] == 'c') {
                        info->c = true;
                    } else if (args[i][j] == 'l') {
                        info->l = true;
                    } else if (args[i][j] == 'n') {
                        info->n = true;
                    } else {
                        fprintf(stderr, "Invalid flags\n");
                    }
                }
                memset(args[i], 0, strlen(args[i]));
            } else if (!first_occurance) {
                first_occurance = true;
                arglen = strlen(args[i]);
                if ((info->pattern[counter] = (char *)calloc(arglen + 1, sizeof(char)))) {
                    strcpy(info->pattern[counter], args[i]);
                    counter++;
                    memset(args[i], 0, arglen);
                } else {
                    ret = 0;
                }
            } else {
                info->files_len++;
            }
        }
    } else {
        ret = 0;
    }
    return ret;
}

int len_of_search_strings(char **args, data *info, bool *first_occurance) {
    int res = 0;
    for (int i = 1; args[i]; i++) {
        if (args[i][0] == '-') {
            for (int j = 1; args[i][j]; j++) {
                if (args[i][j] == 'e') {
                    res++;
                    info->e = true;
                    *first_occurance = true;
                }
            }
        }
    }
    if (res == 0)
        res = 1;
    return res;
}

int search_string(data *info) {
    int rflags = 0;
    int ret = 1;
    info->regex = (regex_t *)calloc(info->len, sizeof(regex_t));
    if (info->regex) {
        if (info->i)
            rflags = REG_ICASE;
        for (int i = 0; i < info->len && ret; i++) {
            if (regcomp(&info->regex[i], info->pattern[i], rflags))
                ret = 0;
        }
    } else {
        ret = 0;
    }
    return ret;
}

void read_files(data info, char **files, int lenfiles) {
    FILE *file;
    for (int i = 1; i < lenfiles; i++) {
        if (files[i][0] != '\0') {
            file = fopen(files[i], "r");
            if (file) {
                print_file(file, info, files[i]);
                fclose(file);
            } else {
                fprintf(stderr, "s21_grep: %s: No such file or directory\n", files[i]);
            }
        }
    }
}

void print_file(FILE *file, data info, char *filename) {
    size_t size = 0;
    int c_counter = 0;
    int n_counter = 0;
    char *line = NULL;
    while (getline(&line, &size, file) != -1) {
        n_counter++;
        if (find_match(info, line) == 0) {
            c_counter++;
            if (info.files_len > 1 && !info.c && !info.l)
                fprintf(stdout, "%s:", filename);
            if (info.n && !info.c && !info.l)
                fprintf(stdout, "%d:", n_counter);
            if (!info.c && !info.l) {
                fprintf(stdout, "%s", line);
                if (line[strlen(line) - 1] != '\n')
                    fprintf(stdout, "\n");
            }
        }
    }
    if (line)
        free(line);
    if (info.c) {
        if (info.files_len > 1)
            fprintf(stdout, "%s:", filename);
        if (info.l && info.files_len > 0 && c_counter != 0)
            c_counter = 1;
        fprintf(stdout, "%d\n", c_counter);
    }
    if (info.l && c_counter > 0) {
        fprintf(stdout, "%s\n", filename);
    }
}

int find_match(data info, char *line) {
    int match = 0;
    for (int i = 0; i < info.len; i++) {
        match = regexec(&info.regex[i], line, 0, NULL, 0);
        if (!match)
            break;
    }
    if (info.v)
        match = !match;
    return match;
}

void free_dat_shit(data info) {
    for (int i = 0; i < info.len; i++) {
        if (info.pattern[i])
            free(info.pattern[i]);
        regfree(&info.regex[i]);
    }
    if (info.pattern)
        free(info.pattern);
    if (info.regex)
        free(info.regex);
}
