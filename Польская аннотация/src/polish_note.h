#ifndef POLISH_NOTE_H
#define POLISH_NOTE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stack;

int prioritet(char oper);
double calc_polsk(char* out, double x);
double to_polsky(char form[100], double x);
int is_function_token(const char* form, int k);
char get_function_code(char func_char);
int is_unary_minus(const char* form, int k);
int handle_operator(char* form, int k, struct stack** Oper, char* output, int* l);
int handle_closing_bracket(struct stack** Oper, char* output, int* l);
int handle_function(char* form, int k, struct stack** Oper);
int handle_number(const char* form, int k, char* output, int* l);
double calculate_binary_operation(char op, double a, double b, int* error);
double calculate_unary_operation(char op, double b, int* error);
int process_token(char* form, int* k, struct stack** Oper, char* output, int* l);
void cleanup_stack(struct stack** Oper);

#endif
