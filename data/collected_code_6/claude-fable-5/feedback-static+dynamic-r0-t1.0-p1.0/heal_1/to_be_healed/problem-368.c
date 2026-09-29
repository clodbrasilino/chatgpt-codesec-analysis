#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple *tuple_create(const int *values, size_t size)
{
    Tuple *t = NULL;

    if (values == NULL || size == 0U) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->elements = malloc(size * sizeof(int));
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->elements, values, size * sizeof(int));
    t->size = size;

    return t;
}

void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0U;
        free(t);
    }
}

Tuple *tuple_repeat(const Tuple *t, size_t n)
{
    Tuple *result = NULL;
    size_t total = 0U;
    size_t i = 0U;

    if (t == NULL || t->elements == NULL || n == 0U) {
        return NULL;
    }

    if (t->size > (SIZE_MAX / sizeof(int)) / n) {
        return NULL;
    }

    total = t->size * n;

    result = malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->elements = malloc(total * sizeof(int));
    if (result->elements == NULL) {
        free(result);
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(&result->elements[i * t->size], t->elements,
               t->size * sizeof(int));
    }

    result->size = total;

    return result;
}

void tuple_print(const Tuple *t)
{
    size_t i = 0U;

    if (t == NULL || t->elements == NULL) {
        printf("(empty)\n");
        return;
    }

    printf("(");
    for (i = 0U; i < t->size; i++) {
        printf("%d", t->elements[i]);
        if (i < t->size - 1U) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int values[] = {1, 2, 3};
    Tuple *original = NULL;
    Tuple *repeated = NULL;
    size_t n = 3U;

    original = tuple_create(values, sizeof(values) / sizeof(values[0]));
    if (original == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    repeated = tuple_repeat(original, n);
    if (repeated == NULL) {
        fprintf(stderr, "Failed to repeat tuple\n");
        tuple_destroy(original);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(original);
    printf("Repeated %zu times: ", n);
    tuple_print(repeated);

    tuple_destroy(original);
    tuple_destroy(repeated);

    return EXIT_SUCCESS;
}