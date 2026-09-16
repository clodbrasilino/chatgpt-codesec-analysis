#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        double d;
        char c;
        char *s;
    } value;
} Element;

typedef struct {
    Element *elements;
    size_t count;
} Tuple;

Element make_int(int v)
{
    Element e;
    e.type = TYPE_INT;
    e.value.i = v;
    return e;
}

Element make_float(float v)
{
    Element e;
    e.type = TYPE_FLOAT;
    e.value.f = v;
    return e;
}

Element make_double(double v)
{
    Element e;
    e.type = TYPE_DOUBLE;
    e.value.d = v;
    return e;
}

Element make_char(char v)
{
    Element e;
    e.type = TYPE_CHAR;
    e.value.c = v;
    return e;
}

Element make_string(const char *v)
{
    Element e;
    size_t len;
    e.type = TYPE_STRING;
    e.value.s = NULL;
    if (v != NULL) {
        len = strlen(v);
        e.value.s = (char *)malloc(len + 1);
        if (e.value.s != NULL) {
            memcpy(e.value.s, v, len + 1);
        }
    }
    return e;
}

size_t remove_type(Tuple *tuple, DataType type)
{
    size_t i;
    size_t write_index;
    size_t removed;

    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }

    write_index = 0;
    removed = 0;

    for (i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == type) {
            if (type == TYPE_STRING && tuple->elements[i].value.s != NULL) {
                free(tuple->elements[i].value.s);
                tuple->elements[i].value.s = NULL;
            }
            removed++;
        } else {
            if (write_index != i) {
                tuple->elements[write_index] = tuple->elements[i];
            }
            write_index++;
        }
    }

    if (write_index < tuple->count) {
        memset(&tuple->elements[write_index], 0,
               (tuple->count - write_index) * sizeof(Element));
    }

    tuple->count = write_index;
    return removed;
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    printf("(");
    for (i = 0; i < tuple->count; i++) {
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", tuple->elements[i].value.i);
                break;
            case TYPE_FLOAT:
                printf("%f", (double)tuple->elements[i].value.f);
                break;
            case TYPE_DOUBLE:
                printf("%f", tuple->elements[i].value.d);
                break;
            case TYPE_CHAR:
                printf("'%c'", tuple->elements[i].value.c);
                break;
            case TYPE_STRING:
                printf("\"%s\"", tuple->elements[i].value.s != NULL
                       ? tuple->elements[i].value.s : "(null)");
                break;
            default:
                printf("?");
                break;
        }
        if (i + 1 < tuple->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

void free_tuple(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (i = 0; i < tuple->count; i++) {
            if (tuple->elements[i].type == TYPE_STRING &&
                tuple->elements[i].value.s != NULL) {
                free(tuple->elements[i].value.s);
                tuple->elements[i].value.s = NULL;
            }
        }
        free(tuple->elements);
        tuple->elements = NULL;
    }
    tuple->count = 0;
}

int main(void)
{
    Tuple tuple;
    size_t removed;
    size_t capacity;

    capacity = 8;
    tuple.elements = (Element *)malloc(capacity * sizeof(Element));
    if (tuple.elements == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }
    tuple.count = capacity;

    tuple.elements[0] = make_int(10);
    tuple.elements[1] = make_string("hello");
    tuple.elements[2] = make_float(3.14f);
    tuple.elements[3] = make_int(20);
    tuple.elements[4] = make_char('A');
    tuple.elements[5] = make_string("world");
    tuple.elements[6] = make_double(2.71828);
    tuple.elements[7] = make_int(30);

    if (tuple.elements[1].value.s == NULL ||
        tuple.elements[5].value.s == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        free_tuple(&tuple);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    print_tuple(&tuple);

    removed = remove_type(&tuple, TYPE_INT);
    printf("Removed %zu integer element(s)\n", removed);
    printf("After removing integers: ");
    print_tuple(&tuple);

    removed = remove_type(&tuple, TYPE_STRING);
    printf("Removed %zu string element(s)\n", removed);
    printf("After removing strings: ");
    print_tuple(&tuple);

    free_tuple(&tuple);

    return EXIT_SUCCESS;
}