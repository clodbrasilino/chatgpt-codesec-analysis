#include <stdio.h>
#include <stdlib.h>

typedef enum { ELEM_INT, ELEM_TUPLE } ElemType;

typedef struct Element Element;

struct Element {
    ElemType type;
    union {
        int value;
        struct {
            Element **items;
            size_t count;
        } tuple;
    } data;
};

static void free_element(Element *e);

static Element *make_int(int value)
{
    Element *e = malloc(sizeof *e);
    if (e == NULL) {
        return NULL;
    }
    e->type = ELEM