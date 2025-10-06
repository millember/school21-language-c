#include "polish_note.h"

#include "lib_struct.h"

int prioritet(char oper) {
    int result = 0;
    if (oper == '(')
        result = 1;
    else if (oper == '+' || oper == '-')
        result = 2;
    else if (oper == '*' || oper == '/')
        result = 3;
    else if (oper == 's' || oper == 't' || oper == 'g' || oper == 'c' || oper == 'l')
        result = 4;
    else if (oper == 'q' || oper == '~')
        result = 5;
    return result;
}

int is_function_token(const char* form, int k) {
    return (form[k] == 's' && form[k + 1] == '(') || (form[k] == 'c' && form[k + 1] == '(') ||
           (form[k] == 't' && form[k + 1] == '(') || (form[k] == 'g' && form[k + 1] == '(') ||
           (form[k] == 'q' && form[k + 1] == '(') || (form[k] == 'l' && form[k + 1] == '(');
}

char get_function_code(char func_char) {
    char result = func_char;
    if (func_char == 's')
        result = SIN;
    else if (func_char == 'c')
        result = COS;
    else if (func_char == 't')
        result = TAN;
    else if (func_char == 'g')
        result = CTG;
    else if (func_char == 'q')
        result = SQRT;
    else if (func_char == 'l')
        result = LN;
    return result;
}

int is_unary_minus(const char* form, int k) {
    return form[k] == '-' && (k == 0 || form[k - 1] == '(' || form[k - 1] == '+' || form[k - 1] == '-' ||
                              form[k - 1] == '*' || form[k - 1] == '/');
}

int handle_operator(char* form, int k, struct stack** Oper, char* output, int* l) {
    int result = k;
    if (is_unary_minus(form, k)) {
        *Oper = instr(*Oper, '~');
    } else {
        while (*Oper != NULL && prioritet((*Oper)->c) >= prioritet(form[k])) {
            char a;
            *Oper = out_t(*Oper, &a);
            output[(*l)++] = a;
            output[(*l)++] = ' ';
        }
        *Oper = instr(*Oper, form[k]);
    }
    result++;
    return result;
}

int handle_closing_bracket(struct stack** Oper, char* output, int* l) {
    int found_paren = 0;
    int error = 0;

    while (*Oper != NULL && (*Oper)->c != '(') {
        char a;
        *Oper = out_t(*Oper, &a);
        output[(*l)++] = a;
        output[(*l)++] = ' ';
    }

    if (*Oper != NULL && (*Oper)->c == '(') {
        struct stack* r = *Oper;
        *Oper = (*Oper)->Next;
        free(r);
        found_paren = 1;
    }

    if (!found_paren) {
        while (*Oper != NULL) {
            char a;
            *Oper = out_t(*Oper, &a);
        }
        error = 1;
    }

    return error;
}

int handle_function(char* form, int k, struct stack** Oper) {
    int result = k;
    char func_code = get_function_code(form[k]);
    *Oper = instr(*Oper, func_code);
    result += 1;
    return result;
}

int handle_number(const char* form, int k, char* output, int* l) {
    int result = k;
    while ((form[result] >= '0' && form[result] <= '9') || form[result] == '.') {
        output[(*l)++] = form[result++];
    }
    output[(*l)++] = ' ';
    return result;
}

double calculate_binary_operation(char op, double a, double b, int* error) {
    double result = 0;
    if (op == '+')
        result = a + b;
    else if (op == '-')
        result = a - b;
    else if (op == '*')
        result = a * b;
    else if (op == '/') {
        if (b == 0)
            *error = 1;
        else
            result = a / b;
    }
    return result;
}

double calculate_unary_operation(char op, double b, int* error) {
    double result = 0;
    if (op == '~') {
        result = -b;
    } else if (op == 's')
        result = sin(b);
    else if (op == 'c')
        result = cos(b);
    else if (op == 't')
        result = tan(b);
    else if (op == 'g') {
        if (tan(b) == 0)
            *error = 1;
        else
            result = 1.0 / tan(b);
    } else if (op == 'q') {
        if (b < 0)
            *error = 1;
        else
            result = sqrt(b);
    } else if (op == 'l') {
        if (b <= 0)
            *error = 1;
        else
            result = log(b);
    }
    return result;
}

double calc_polsk(char* out, double x) {
    double s[1000] = {0};
    int t = -1;
    char* tok = strtok(out, " ");
    double result = NAN;
    int error = 0;

    while (tok != NULL && !error) {
        if (strcmp(tok, "x") == 0) {
            s[++t] = x;
        } else if (tok[0] >= '0' && tok[0] <= '9') {
            s[++t] = atof(tok);
        } else {
            double b = s[t--];
            double res = 0;

            if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/') {
                double a = s[t--];
                res = calculate_binary_operation(tok[0], a, b, &error);
            } else {
                res = calculate_unary_operation(tok[0], b, &error);
                if (tok[0] == '~') t++;
            }

            if (!error) s[++t] = res;
        }
        tok = strtok(NULL, " ");
    }

    if (!error && t >= 0) result = s[t];
    return result;
}

double to_polsky(char form[100], double x) {
    struct stack* Oper = NULL;
    char output[1000];
    int k = 0, l = 0;
    int error = 0;

    while (form[k] != '\0' && !error) {
        error = process_token(form, &k, &Oper, output, &l);
    }

    while (Oper != NULL && !error) {
        char a;
        Oper = out_t(Oper, &a);
        output[l++] = a;
        output[l++] = ' ';
    }

    output[l] = '\0';
    double res = error ? NAN : calc_polsk(output, x);

    cleanup_stack(&Oper);
    return res;
}

int process_token(char* form, int* k, struct stack** Oper, char* output, int* l) {
    int error = 0;

    if (form[*k] == ')') {
        error = handle_closing_bracket(Oper, output, l);
        (*k)++;
    } else if (is_function_token(form, *k)) {
        *k = handle_function(form, *k, Oper);
    } else if (form[*k] == 'x') {
        output[(*l)++] = 'x';
        output[(*l)++] = ' ';
        (*k)++;
    } else if (form[*k] >= '0' && form[*k] <= '9') {
        *k = handle_number(form, *k, output, l);
    } else if (form[*k] == '(') {
        *Oper = instr(*Oper, '(');
        (*k)++;
    } else if (strchr("+-*/", form[*k]) != NULL) {
        *k = handle_operator(form, *k, Oper, output, l);
    } else {
        (*k)++;
    }

    return error;
}

void cleanup_stack(struct stack** Oper) {
    while (*Oper != NULL) {
        char a;
        *Oper = out_t(*Oper, &a);
    }
}
