#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        double d;
        char c;
        char *s;
    } value;
} Element;

typedef struct {
    Element *items;
    size_t size;
    size_t capacity;
} Tuple;

static int tuple_init(Tuple *t, size_t capacity)
{
    if (t == NULL || capacity == 0) {
        return -1;
    }
    t->items = (Element *)calloc(capacity, sizeof(Element));
    if (t->items == NULL) {
        t->size = 0;
        t->capacity = 0;
        return -1;
    }
    t->size = 0;
    t->capacity = capacity;
    return 0;
}

static int tuple_grow(Tuple *t)
{
    size_t new_capacity;
    Element *new_items;

    if (t == NULL || t->capacity == 0) {
        return -1;
    }
    if (t->capacity > ((size_t)-1) / 2 / sizeof(Element)) {
        return -1;
    }
    new_capacity = t->capacity * 2;
    new_items = (Element *)realloc(t->items, new_capacity * sizeof(Element));
    if (new_items == NULL) {
        return -1;
    }
    t->items = new_items;
    t->capacity = new_capacity;
    return 0;
}

static int tuple_add_int(Tuple *t, int v)
{
    if (t == NULL) {
        return -1;
    }
    if (t->size == t->capacity && tuple_grow(t) != 0) {
        return -1;
    }
    t->items[t->size].type = TYPE_INT;
    t->items[t->size].value.i = v;
    t->size++;
    return 0;
}

static int tuple_add_double(Tuple *t, double v)
{
    if (t == NULL) {
        return -1;
    }
    if (t->size == t->capacity && tuple_grow(t) != 0) {
        return -1;
    }
    t->items[t->size].type = TYPE_DOUBLE;
    t->items[t->size].value.d = v;
    t->size++;
    return 0;
}

static int tuple_add_char(Tuple *t, char v)
{
    if (t == NULL) {
        return -1;
    }
    if (t->size == t->capacity && tuple_grow(t) != 0) {
        return -1;
    }
    t->items[t->size].type = TYPE_CHAR;
    t->items[t->size].value.c = v;
    t->size++;
    return 0;
}

static int tuple_add_string(Tuple *t, const char *v)
{
    size_t len;
    char *copy;

    if (t == NULL || v == NULL) {
        return -1;
    }
    if (t->size == t->capacity && tuple_grow(t) != 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(v);
    if (len == (size_t)-1) {
        return -1;
    }
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, v, len + 1);
    t->items[t->size].type = TYPE_STRING;
    t->items[t->size].value.s = copy;
    t->size++;
    return 0;
}

static size_t tuple_remove_type(Tuple *t, DataType type)
{
    size_t i;
    size_t write_index = 0;
    size_t removed = 0;

    if (t == NULL) {
        return 0;
    }
    for (i = 0; i < t->size; i++) {
        if (t->items[i].type == type) {
            if (type == TYPE_STRING && t->items[i].value.s != NULL) {
                free(t->items[i].value.s);
                t->items[i].value.s = NULL;
            }
            removed++;
        } else {
            if (write_index != i) {
                t->items[write_index] = t->items[i];
            }
            write_index++;
        }
    }
    t->size = write_index;
    return removed;
}

static void tuple_print(const Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }
    printf("(");
    for (i = 0; i < t->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        switch (t->items[i].type) {
        case TYPE_INT:
            printf("%d", t->items[i].value.i);
            break;
        case TYPE_DOUBLE:
            printf("%g", t->items[i].value.d);
            break;
        case TYPE_CHAR:
            printf("'%c'", t->items[i].value.c);
            break;
        case TYPE_STRING:
            printf("\"%s\"", t->items[i].value.s);
            break;
        default:
            printf("<unknown>");
            break;
        }
    }
    printf(")\n");
}

static void tuple_free(Tuple *t)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (t == NULL) {
        return;
    }
    if (t->items != NULL) {
        for (i = 0; i < t->size; i++) {
            if (t->items[i].type == TYPE_STRING && t->items[i].value.s != NULL) {
                free(t->items[i].value.s);
                t->items[i].value.s = NULL;
            }
        }
        free(t->items);
        t->items = NULL;
    }
    t->size = 0;
    t->capacity = 0;
}

int main(void)
{
    Tuple t;
    size_t removed;

    if (tuple_init(&t, 4) != 0) {
        fprintf(stderr, "Error: failed to initialize tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(&t, 10) != 0 ||
        tuple_add_string(&t, "hello") != 0 ||
        tuple_add_double(&t, 3.14) != 0 ||
        tuple_add_char(&t, 'A') != 0 ||
        tuple_add_int(&t, 20) != 0 ||
        tuple_add_string(&t, "world") != 0 ||
        tuple_add_double(&t, 2.71) != 0) {
        fprintf(stderr, "Error: failed to add element\n");
        tuple_free(&t);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(&t);

    removed = tuple_remove_type(&t, TYPE_INT);
    printf("Removed %zu element(s) of type int\n", removed);
    printf("Resulting tuple: ");
    tuple_print(&t);

    removed = tuple_remove_type(&t, TYPE_STRING);
    printf("Removed %zu element(s) of type string\n", removed);
    printf("Resulting tuple: ");
    tuple_print(&t);

    tuple_free(&t);
    return EXIT_SUCCESS;
}