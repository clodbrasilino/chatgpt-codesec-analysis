#include <stdio.h>
#include <stdlib.h>

typedef enum { ELEM_INT, ELEM_TUPLE } ElemType;

typedef struct Tuple Tuple;

typedef struct Element {
    ElemType type;
    union {
        int value;
        Tuple *tuple;
    } data;
} Element;

struct Tuple {
    Element *items;
    size_t count;
};

static Tuple *tuple_create(size_t count);
static void tuple_free(Tuple *t);
static Tuple *remove_nested(const Tuple *t);
static void tuple_print(const Tuple *t);

static Tuple *tuple_create(size_t count)
{
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->count = count;
    if (count > 0U) {
        t->items = calloc(count, sizeof(Element));
        if (t->items == NULL) {
            free(t);
            return NULL;
        }
    } else {
        t->items = NULL;
    }
    return t;
}

static void tuple_free(Tuple *t)
{
    if (t == NULL) {
        return;
    }
    for (size_t i = 0U; i < t->count; i++) {
        if (t->items[i].type == ELEM_TUPLE) {
            tuple_free(t->items[i].data.tuple);
        }
    }
    free(t->items);
    free(t);
}

static Tuple *remove_nested(const Tuple *t)
{
    if (t == NULL) {
        return NULL;
    }
    size_t kept = 0U;
    for (size_t i = 0U; i < t->count; i++) {
        if (t->items[i].type == ELEM_INT) {
            kept++;
        }
    }
    Tuple *result = tuple_create(kept);
    if (result == NULL) {
        return NULL;
    }
    size_t j = 0U;
    for (size_t i = 0U; i < t->count; i++) {
        if (t->items[i].type == ELEM_INT) {
            result->items[j].type = ELEM_INT;
            result->items[j].data.value = t->items[i].data.value;
            j++;
        }
    }
    return result;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (size_t i = 0U; i < t->count; i++) {
        if (t->items[i].type == ELEM_INT) {
            printf("%d", t->items[i].data.value);
        } else {
            printf("(");
            const Tuple *inner = t->items[i].data.tuple;
            if (inner != NULL) {
                for (size_t k = 0U; k < inner->count; k++) {
                    if (inner->items[k].type == ELEM_INT) {
                        printf("%d", inner->items[k].data.value);
                    }
                    if ((k + 1U) < inner->count) {
                        printf(", ");
                    }
                }
            }
            printf(")");
        }
        if ((i + 1U) < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    Tuple *inner = tuple_create(2U);
    if (inner == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    inner->items[0].type = ELEM_INT;
    inner->items[0].data.value = 4;
    inner->items[1].type = ELEM_INT;
    inner->items[1].data.value = 6;

    Tuple *original = tuple_create(5U);
    if (original == NULL) {
        tuple_free(inner);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    original->items[0].type = ELEM_INT;
    original->items[0].data.value = 1;
    original->items[1].type = ELEM_INT;
    original->items[1].data.value = 5;
    original->items[2].type = ELEM_INT;
    original->items[2].data.value = 7;
    original->items[3].type = ELEM_TUPLE;
    original->items[3].data.tuple = inner;
    original->items[4].type = ELEM_INT;
    original->items[4].data.value = 10;

    printf("Original tuple: ");
    tuple_print(original);

    Tuple *flattened = remove_nested(original);
    if (flattened == NULL) {
        tuple_free(original);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("After removing nested record: ");
    tuple_print(flattened);

    tuple_free(flattened);
    tuple_free(original);

    return EXIT_SUCCESS;
}