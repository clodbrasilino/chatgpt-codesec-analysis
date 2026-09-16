#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
    e->type = ELEM_INT;
    e->data.value = value;
    return e;
}

static Element *make_tuple(size_t count, ...)
{
    Element *e = malloc(sizeof *e);
    if (e == NULL) {
        return NULL;
    }
    e->type = ELEM_TUPLE;
    e->data.tuple.count = count;
    e->data.tuple.items = malloc(count * sizeof *e->data.tuple.items);
    if (e->data.tuple.items == NULL && count > 0) {
        free(e);
        return NULL;
    }

    va_list args;
    va_start(args, count);
    for (size_t i = 0; i < count; i++) {
        e->data.tuple.items[i] = va_arg(args, Element *);
    }
    va_end(args);

    return e;
}

static void free_element(Element *e)
{
    if (e == NULL) {
        return;
    }
    if (e->type == ELEM_TUPLE) {
        for (size_t i = 0; i < e->data.tuple.count; i++) {
            free_element(e->data.tuple.items[i]);
        }
        free(e->data.tuple.items);
    }
    free(e);
}

static void print_element(const Element *e)
{
    if (e == NULL) {
        printf("(null)");
        return;
    }
    if (e->type == ELEM_INT) {
        printf("%d", e->data.value);
    } else {
        printf("(");
        for (size_t i = 0; i < e->data.tuple.count; i++) {
            if (i > 0) {
                printf(", ");
            }
            print_element(e->data.tuple.items[i]);
        }
        printf(")");
    }
}

int main(void)
{
    Element *a = make_int(1);
    Element *b = make_int(2);
    Element *c = make_int(3);
    if (a == NULL || b == NULL || c == NULL) {
        free_element(a);
        free_element(b);
        free_element(c);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    Element *inner = make_tuple(2, b, c);
    if (inner == NULL) {
        free_element(a);
        free_element(b);
        free_element(c);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    Element *outer = make_tuple(2, a, inner);
    if (outer == NULL) {
        free_element(a);
        free_element(inner);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    print_element(outer);
    printf("\n");

    free_element(outer);
    return EXIT_SUCCESS;
}