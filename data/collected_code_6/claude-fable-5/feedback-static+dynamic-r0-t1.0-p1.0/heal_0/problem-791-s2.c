#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    ELEM_INT,
    ELEM_TUPLE
} ElemType;

typedef struct Tuple Tuple;

typedef struct {
    ElemType type;
    union {
        int value;
        Tuple *tuple;
    } data;
} Element;

struct Tuple {
    Element *items;
    size_t count;
    size_t capacity;
};

Tuple *tuple_create(void);
void tuple_free(Tuple *t);
int tuple_add_int(Tuple *t, int value);
int tuple_add_tuple(Tuple *t, Tuple *nested);
Tuple *remove_nested(const Tuple *t);
void tuple_print(const Tuple *t);

Tuple *tuple_create(void)
{
    Tuple *t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }
    t->items = NULL;
    t->count = 0;
    t->capacity = 0;
    return t;
}

static int tuple_grow(Tuple *t)
{
    size_t new_capacity;
    Element *tmp;

    if (t->count < t->capacity) {
        return 0;
    }
    new_capacity = (t->capacity == 0) ? 4U : t->capacity * 2U;
    if (new_capacity > SIZE_MAX / sizeof(Element)) {
        return -1;
    }
    tmp = realloc(t->items, new_capacity * sizeof(Element));
    if (tmp == NULL) {
        return -1;
    }
    t->items = tmp;
    t->capacity = new_capacity;
    return 0;
}

int tuple_add_int(Tuple *t, int value)
{
    if (t == NULL) {
        return -1;
    }
    if (tuple_grow(t) != 0) {
        return -1;
    }
    t->items[t->count].type = ELEM_INT;
    t->items[t->count].data.value = value;
    t->count++;
    return 0;
}

int tuple_add_tuple(Tuple *t, Tuple *nested)
{
    if (t == NULL || nested == NULL) {
        return -1;
    }
    if (tuple_grow(t) != 0) {
        return -1;
    }
    t->items[t->count].type = ELEM_TUPLE;
    t->items[t->count].data.tuple = nested;
    t->count++;
    return 0;
}

void tuple_free(Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }
    for (i = 0; i < t->count; i++) {
        if (t->items[i].type == ELEM_TUPLE) {
            tuple_free(t->items[i].data.tuple);
        }
    }
    free(t->items);
    free(t);
}

Tuple *remove_nested(const Tuple *t)
{
    Tuple *result;
    size_t i;

    if (t == NULL) {
        return NULL;
    }
    result = tuple_create();
    if (result == NULL) {
        return NULL;
    }
    for (i = 0; i < t->count; i++) {
        if (t->items[i].type == ELEM_INT) {
            if (tuple_add_int(result, t->items[i].data.value) != 0) {
                tuple_free(result);
                return NULL;
            }
        }
    }
    return result;
}

void tuple_print(const Tuple *t)
{
    size_t i;

    if (t == NULL) {
        printf("()");
        return;
    }
    printf("(");
    for (i = 0; i < t->count; i++) {
        if (i > 0) {
            printf(", ");
        }
        if (t->items[i].type == ELEM_INT) {
            printf("%d", t->items[i].data.value);
        } else {
            tuple_print(t->items[i].data.tuple);
        }
    }
    printf(")");
}

int main(void)
{
    Tuple *original;
    Tuple *nested;
    Tuple *result;

    original = tuple_create();
    if (original == NULL) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    nested = tuple_create();
    if (nested == NULL) {
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(nested, 4) != 0 ||
        tuple_add_int(nested, 6) != 0) {
        tuple_free(nested);
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(original, 1) != 0 ||
        tuple_add_int(original, 5) != 0 ||
        tuple_add_int(original, 7) != 0) {
        tuple_free(nested);
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_tuple(original, nested) != 0) {
        tuple_free(nested);
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(original, 10) != 0) {
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(original);
    printf("\n");

    result = remove_nested(original);
    if (result == NULL) {
        tuple_free(original);
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Tuple after removing nested record: ");
    tuple_print(result);
    printf("\n");

    tuple_free(result);
    tuple_free(original);

    return EXIT_SUCCESS;
}