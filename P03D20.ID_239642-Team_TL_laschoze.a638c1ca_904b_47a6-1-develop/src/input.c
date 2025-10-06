#include "input.h"

#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int contains(const char *str, const char *sub) { return strstr(str, sub) != NULL; }
void read_input(char *stroke, int *exit_flag) {
    if (fgets(stroke, MAX_LEN, stdin) == NULL) {
        *exit_flag = 1;
        return;
    }
    size_t len = strlen(stroke);
    if (len > 0 && stroke[len - 1] == '\n') {
        stroke[len - 1] = '\0';
    }
    if (stroke[0] == '\n' || stroke[0] == '.' || stroke[0] == '*' || stroke[0] == '/' || stroke[0] == '+' ||
        contains(stroke, "()")) {
        *exit_flag = 1;
    }
}
void handle_s(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag) {
    size_t total_len = strlen(stroke);
    if (*i + 3 < total_len && stroke[*i + 1] == 'i' && stroke[*i + 2] == 'n' && stroke[*i + 3] == '(') {
        symbols[*id_symb] = 's';
        (*id_symb)++;
        *i += 2;
    } else if (*i + 4 < total_len && stroke[*i + 1] == 'q' && stroke[*i + 2] == 'r' &&
               stroke[*i + 3] == 't' && stroke[*i + 4] == '(') {
        symbols[*id_symb] = 'q';
        (*id_symb)++;
        *i += 3;
    } else {
        *exit_flag = 1;
    }
}

void handle_c(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag) {
    size_t total_len = strlen(stroke);
    if (*i + 3 < total_len && stroke[*i + 1] == 'o' && stroke[*i + 2] == 's' && stroke[*i + 3] == '(') {
        symbols[*id_symb] = 'c';
        (*id_symb)++;
        *i += 2;
    } else if (*i + 3 < total_len && stroke[*i + 1] == 't' && stroke[*i + 2] == 'g' &&
               stroke[*i + 3] == '(') {
        symbols[*id_symb] = 'g';
        (*id_symb)++;
        *i += 2;
    } else {
        *exit_flag = 1;
    }
}

void handle_t(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag) {
    size_t total_len = strlen(stroke);
    if (*i + 3 < total_len && stroke[*i + 1] == 'a' && stroke[*i + 2] == 'n' && stroke[*i + 3] == '(') {
        symbols[*id_symb] = 't';
        (*id_symb)++;
        *i += 2;
    } else {
        *exit_flag = 1;
    }
}

void handle_l(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag) {
    size_t total_len = strlen(stroke);
    if (*i + 2 < total_len && stroke[*i + 1] == 'n' && stroke[*i + 2] == '(') {
        symbols[*id_symb] = 'l';
        (*id_symb)++;
        *i += 1;
    } else {
        *exit_flag = 1;
    }
}

void process_char(char c, size_t *i, int *id_symb, char *symbols, int *exit_flag, char *stroke) {
    if (c == 's') {
        handle_s(stroke, i, id_symb, symbols, exit_flag);
    } else if (c == 'c') {
        handle_c(stroke, i, id_symb, symbols, exit_flag);
    } else if (c == 't') {
        handle_t(stroke, i, id_symb, symbols, exit_flag);
    } else if (c == 'l') {
        handle_l(stroke, i, id_symb, symbols, exit_flag);
    } else if (strchr("+-*/x()", c) != NULL) {
        symbols[*id_symb] = c;
        (*id_symb)++;
    } else if ((c >= '0' && c <= '9') || c == '.') {
        symbols[*id_symb] = c;
        (*id_symb)++;
    } else {
        *exit_flag = 1;
    }
}

void input(char *symbols, int *exit_flag) {
    char stroke[MAX_LEN];
    int id_symb = 0;
    int sk_val1 = 0, sk_val2 = 0;

    read_input(stroke, exit_flag);

    size_t chars_v = strlen(stroke);
    for (size_t i = 0; i < chars_v; i++) {
        char c = stroke[i];
        if (c == 's') {
            handle_s(stroke, &i, &id_symb, symbols, exit_flag);
        } else if (c == 'c') {
            handle_c(stroke, &i, &id_symb, symbols, exit_flag);
        } else if (c == 't') {
            handle_t(stroke, &i, &id_symb, symbols, exit_flag);
        } else if (c == 'l') {
            handle_l(stroke, &i, &id_symb, symbols, exit_flag);
        } else {
            process_char(c, &i, &id_symb, symbols, exit_flag, stroke);
        }
        if (c == '(') sk_val1++;
        if (c == ')') sk_val2++;
    }
    if (sk_val1 != sk_val2) *exit_flag = 1;
    symbols[id_symb] = '\0';
}
