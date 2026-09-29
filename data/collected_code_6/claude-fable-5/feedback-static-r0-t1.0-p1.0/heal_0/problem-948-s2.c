#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TUPLE_INT,
    TUPLE_DOUBLE,
    TUPLE_STRING
} TupleType;

typedef struct {
    TupleType type;
    union {
        int i;
        double d;
        char *s;
    } value;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t size;
} Tuple;

Tuple *tuple_create(size_t size)
{
    Tuple *t;

    if (size == 0) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->items = calloc(size, sizeof(TupleItem));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }

    t->size = size;
    return t;
}

int tuple_set_int(Tuple *t, size_t index, int value)
{
    if (t == NULL || index >= t->size) {
        return -1;
    }
    t->items[index].type = TUPLE_INT;
    t->items[index].value.i = value;
    return 0;
}

int tuple_set_double(Tuple *t, size_t index, double value)
{
    if (t == NULL || index >= t->size) {
        return -1;
    }
    t->items[index].type = TUPLE_DOUBLE;
    t->items[index].value.d = value;
    return 0;
}

int tuple_set_string(Tuple *t, size_t index, const char *value)
{
    char *copy;
    size_t len;

    if (t == NULL || index >= t->size || value == NULL) {
        return -1;
    }

    len = strlen(value);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return -1;
    }
    memcpy(copy, value, len + 1);

    if (t->items[index].type == TUPLE_STRING && t->items[index].value.s != NULL) {
        free(t->items[index].value.s);
    }

    t->items[index].type = TUPLE_STRING;
    t->items[index].value.s = copy;
    return 0;
}

const TupleItem *tuple_get_item(const Tuple *t, size_t index)
{
    if (t == NULL || index >= t->size) {
        return NULL;
    }
    return &t->items[index];
}

void tuple_destroy(Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }

    for (i = 0; i < t->size; i++) {
        if (t->items[i].type == TUPLE_STRING && t->items[i].value.s != NULL) {
            free(t->items[i].value.s);
            t->items[i].value.s = NULL;
        }
    }

    free(t->items);
    free(t);
}

static void print_item(const TupleItem *item)
{
    if (item == NULL) {
        printf("Item not found\n");
        return;
    }

    switch (item->type) {
    case TUPLE_INT:
        printf("Int: %d\n", item->value.i);
        break;
    case TUPLE_DOUBLE:
        printf("Double: %f\n", item->value.d);
        break;
    case TUPLE_STRING:
        printf("String: %s\n", item->value.s != NULL ? item->value.s : "(null)");
        break;
    default:
        printf("Unknown type\n");
        break;
    }
}

int main(void)
{
    Tuple *t;
    const TupleItem *item;
    size_t i;

    t = tuple_create(3);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_set_int(t, 0, 42) != 0 ||
        tuple_set_double(t, 1, 3.14) != 0 ||
        tuple_set_string(t, 2, "hello") != 0) {
        fprintf(stderr, "Failed to set tuple items\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 3; i++) {
        item = tuple_get_item(t, i);
        print_item(item);
    }

    item = tuple_get_item(t, 10);
    if (item == NULL) {
        printf("Index 10 is out of bounds\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}