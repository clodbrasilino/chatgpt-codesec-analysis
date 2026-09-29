#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    int *values;
} Tuple;

int tuple_subtract(const Tuple *left, const Tuple *right, Tuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->size != right->size ||
        (left->size > 0 && (left->values == NULL || right->values == NULL))) {
        return -1;
    }

    result->size = 0;
    result->values = NULL;

    if (left->size == 0) {
        return 0;
    }

    if (left->size > SIZE_MAX / sizeof(*result->values)) {
        return -1;
    }

    result->values = malloc(left->size * sizeof(*result->values));
    if (result->values == NULL) {
        return -1;
    }

    result->size = left->size;

    for (size_t i = 0; i < left->size; ++i) {
        result->values[i] = left->values[i] - right->values[i];
    }

    return 0;
}

void tuple_destroy(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0;
    }
}

int main(void)
{
    int left_values[] = {10, 20, 30, 40};
    int right_values[] = {1, 2, 3, 4};
    Tuple left = {4, left_values};
    Tuple right = {4, right_values};
    Tuple result = {0, NULL};

    if (tuple_subtract(&left, &right, &result) != 0) {
        fputs("Tuple subtraction failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.size; ++i) {
        printf("%d%s", result.values[i], i + 1 < result.size ? " " : "\n");
    }

    tuple_destroy(&result);
    return EXIT_SUCCESS;
}