#ifndef LIB_STRUCT_H
#define LIB_STRUCT_H
#include <stdlib.h>

#define SIN 's'
#define TAN 't'
#define CTG 'g'
#define SQRT 'q'
#define COS 'c'
#define LN 'l'

struct stack {
    char c;
    struct stack *Next;
};

struct stack *instr(struct stack *r, char s) {
    struct stack *elem = malloc(sizeof(struct stack));
    elem->c = s;
    elem->Next = r;
    return elem;
}
struct stack *out_t(struct stack *r, char *s) {
    if (r == NULL) return NULL;
    struct stack *elem = r;
    *s = r->c;
    r = r->Next;
    free(elem);
    return r;
}

#endif
