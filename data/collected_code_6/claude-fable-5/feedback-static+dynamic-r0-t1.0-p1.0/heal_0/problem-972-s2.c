#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

static Tuple *tuple_create(const int *values, size_t size)
{
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    if (size > 0U) {
        t->elements = malloc(size * sizeof(int));
        if (t->elements == NULL) {
            free(t);
            return NULL;
        }
        for (size_t i = 0U; i < size; i++) {
            t->elements[i] = values[i];
        }
    } else {
        t->elements = NULL;
    }

    t->size = size;
    return t;
}

static void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        free(t);
    }
}

static Tuple *tuple_concatenate(const Tuple *a, const Tuple *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    size_t total = a->size + b->size;
    if (total < a->size) {
        return NULL;
    }

    Tuple *result = malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    if (total > 0U) {
        result->elements = malloc(total * sizeof(int));
        if (result->elements == NULL) {
            free(result);
            return NULL;
        }
        for (size_t i = 0U; i < a->size; i++) {
            result->elements[i] = a->elements[i];
        }
        for (size_t i = 0U; i < b->size; i++) {
            result->elements[a->size + i] = b->elements[i];
        }
    } else {
        result->elements = NULL;
    }

    result->size = total;
    return result;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("(null)\n");
        return;
    }

    printf("(");
    for (size_t i = 0U; i < t->size; i++) {
        printf("%d", t->elements[i]);
        if (i + 1U < t->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int values1[] = {3, 4};
    int values2[] = {5, 6};

    Tuple *t1 = tuple_create(values1, sizeof(values1) / sizeof(values1[0]));
    if (t1 == NULL) {
        fprintf(stderr, "Failed to create first tuple\n");
        return EXIT_FAILURE;
    }

    Tuple *t2 = tuple_create(values2, sizeof(values2) / sizeof(values2[0]));
    if (t2 == NULL) {
        fprintf(stderr, "Failed to create second tuple\n");
        tuple_destroy(t1);
        return EXIT_FAILURE;
    }

    Tuple *result = tuple_concatenate(t1, t2);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate tuples\n");
        tuple_destroy(t1);
        tuple_destroy(t2);
        return EXIT_FAILURE;
    }

    printf("Tuple 1: ");
    tuple_print(t1);
    printf("Tuple 2: ");
    tuple_print(t2);
    printf("Concatenated: ");
    tuple_print(result);

    tuple_destroy(t1);
    tuple_destroy(t2);
    tuple_destroy(result);

    return EXIT_SUCCESS;
}