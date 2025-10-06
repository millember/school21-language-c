#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#define MAX_LEN 100
int contains(const char *str, const char *sub);
void read_input(char *stroke, int *exit_flag);
void handle_s(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag);
void handle_c(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag);
void handle_t(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag);
void handle_l(char *stroke, size_t *i, int *id_symb, char *symbols, int *exit_flag);
void process_char(char c, size_t *i, int *id_symb, char *symbols, int *exit_flag, char *stroke);
void input(char *symbols, int *exit_flag);

#endif
