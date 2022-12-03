#include "s21_cat.h"

int main(int ac, char **av) {
    data flags = {0};
    if (ac > 1) {
        if (parser(av, &flags))
            read_files(av, ac, flags);
    } else {
        fprintf(stderr, "Incorrect arguments\n");
    }
    return 0;
}

int parser(char **av, data *info) {
    int ret = 1;
    for (int i = 1; av[i]; i++) {
        if (av[i][0] == '-') {
            for (int j = 1; av[i][j]; j++) {
                if (av[i][j] == 'b') {
                    info->b = true;
                } else if (av[i][j] == 'e') {
                    info->e = true;
                } else if (av[i][j] == 'E') {
                    info->E = true;
                } else if (av[i][j] == 'T') {
                    info->T = true;
                } else if (av[i][j] == 'n') {
                    info->n = true;
                } else if (av[i][j] == 's') {
                    info->s = true;
                } else if (av[i][j] == 't') {
                    info->t = true;
                } else if (av[i][j] == 'v') {
                    info->v = true;
                } else if (av[i][j] == '-') {
                    if (strcmp(av[i], "--number-nonblank") == 0)
                        info->b = true;
                    if (strcmp(av[i], "--number") == 0)
                        info->n = true;
                    if (strcmp(av[i], "--squeeze-blank") == 0)
                        info->s = true;
                    break;
                } else {
                    fprintf(stderr, "Incorrect flags\n");
                    ret = 0;
                }
            }
            memset(av[i], 0, strlen(av[i]));
        }
    }
    if (info->b && info->n)
        info->n = false;
    return ret;
}

void read_files(char **str, int files_num, data flags) {
    FILE *file = NULL;
    for (int i = 1; i < files_num; i++) {
        if (str[i][0] != '\0') {
            file = fopen(str[i], "r");
            if (file != NULL) {
                print_file(file, flags);
                fclose(file);
            } else {
                perror("File error");
            }
        }
    }
}

int print_file(FILE *file, data flags) {
    char c = 0;
    char pre = '\n';
    char pre_pre = 0;
    int b_counter = 1;
    bool new_line = true;
    while ((c = fgetc(file)) != EOF) {
        if (flags.s == true) {
            if (pre == '\n' && c == '\n' && pre_pre == '\n')
                continue;
        }
        if (flags.b == true) {
            if (pre =='\n' && c != '\n') printf("%6d\t", b_counter++);
        }
        if (flags.n == true) {
            if (new_line == true)
                printf("%6d\t", b_counter++);
            new_line = (c == '\n');
        }
        if (flags.e == true || flags.E == true) {
            if (!flags.E && (print_nonprint(c)) == 1)
                continue;
            if (c == '\n')
                putc('$', stdout);
        }
        if (flags.t == true || flags.T == true) {
            if (!flags.T && (print_nonprint(c)) == 1)
                continue;
            if (c == '\t') {
                printf("^I");
                continue;
            }
        }
        if (flags.v == true) {
            if ((print_nonprint(c)) == 1)
                continue;
        }
        putc(c, stdout);
        pre_pre = pre;
        pre = c;
    }
    return 0;
}

int print_nonprint(char a) {
    int res = 0;
    unsigned char c = a;
    if (is_nonprint(c)) {
        fputs(spec_symbols[c], stdout);
        res = 1;
    }
    return res;
}

int is_nonprint(unsigned char a) { return (a <= 8) || (a >= 11 && a <=31) || (a >= 127 && a <= 159); }
