#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} NestedTuple;

static void free_nested_tuple(NestedTuple *nested)
{
    if (nested == NULL) {
        return;
    }

    for (size_t i = 0; i < nested->size; ++i) {
        free(nested->tuples[i].elements);
    }

    free(nested->tuples);
    nested->tuples = NULL;
    nested->size = 0;
}

static int add_nested_tuples(
    const NestedTuple *left,
    const NestedTuple *right,
    NestedTuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->size != right->size) {
        return 0;
    }

    result->tuples = NULL;
    result->size = 0;

    if (left->size == 0) {
        return 1;
    }

    result->tuples = calloc(left->size, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        return 0;
    }

    result->size = left->size;

    for (size_t i = 0; i < left->size; ++i) {
        if (left->tuples[i].size != right->tuples[i].size) {
            free_nested_tuple(result);
            return 0;
        }

        result->tuples[i].size = left->tuples[i].size;

        if (result->tuples[i].size == 0) {
            continue;
        }

        result->tuples[i].elements =
            malloc(result->tuples[i].size * sizeof(*result->tuples[i].elements));

        if (result->tuples[i].elements == NULL) {
            free_nested_tuple(result);
            return 0;
        }

        for (size_t j = 0; j < result->tuples[i].size; ++j) {
            result->tuples[i].elements[j] =
                left->tuples[i].elements[j] + right->tuples[i].elements[j];
        }
    }

    return 1;
}

static void print_nested_tuple(const NestedTuple *nested)
{
    if (nested == NULL) {
        return;
    }

    putchar('(');

    for (size_t i = 0; i < nested->size; ++i) {
        putchar('(');

        for (size_t j = 0; j < nested->tuples[i].size; ++j) {
            printf("%d", nested->tuples[i].elements[j]);

            if (j + 1 < nested->tuples[i].size) {
                printf(", ");
            }
        }

        putchar(')');

        if (i + 1 < nested->size) {
            printf(", ");
        }
    }

    printf(")\n");
}

int main(void)
{
    int left_first[] = {1, 2, 3};
    int left_second[] = {4, 5};
    int right_first[] = {6, 7, 8};
    int right_second[] = {9, 10};

    Tuple left_tuples[] = {
        {left_first, sizeof(left_first) / sizeof(left_first[0])},
        {left_second, sizeof(left_second) / sizeof(left_second[0])}
    };

    Tuple right_tuples[] = {
        {right_first, sizeof(right_first) / sizeof(right_first[0])},
        {right_second, sizeof(right_second) / sizeof(right_second[0])}
    };

    NestedTuple left = {
        left_tuples,
        sizeof(left_tuples) / sizeof(left_tuples[0])
    };

    NestedTuple right = {
        right_tuples,
        sizeof(right_tuples) / sizeof(right_tuples[0])
    };

    NestedTuple result = {NULL, 0};

    if (!add_nested_tuples(&left, &right, &result)) {
        fprintf(stderr, "Unable to add nested tuples.\n");
        return EXIT_FAILURE;
    }

    print_nested_tuple(&result);
    free_nested_tuple(&result);

    return EXIT_SUCCESS;
}