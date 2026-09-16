#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    int *elements;
} Tuple;

typedef struct {
    size_t size;
    Tuple *tuples;
} NestedTuple;

typedef enum {
    SUBTRACT_SUCCESS = 0,
    SUBTRACT_INVALID_ARGUMENT,
    SUBTRACT_SHAPE_MISMATCH,
    SUBTRACT_OVERFLOW,
    SUBTRACT_ALLOCATION_FAILURE
} SubtractResult;

static void free_nested_tuple(NestedTuple *nested)
{
    if (nested == NULL) {
        return;
    }

    if (nested->tuples != NULL) {
        for (size_t i = 0; i < nested->size; ++i) {
            free(nested->tuples[i].elements);
            nested->tuples[i].elements = NULL;
            nested->tuples[i].size = 0;
        }

        free(nested->tuples);
    }

    nested->tuples = NULL;
    nested->size = 0;
}

static SubtractResult subtract_nested_tuples(
    const NestedTuple *left,
    const NestedTuple *right,
    NestedTuple *result)
{
    if (left == NULL || right == NULL || result == NULL || result == left ||
        result == right || (left->size > 0 && left->tuples == NULL) ||
        (right->size > 0 && right->tuples == NULL)) {
        return SUBTRACT_INVALID_ARGUMENT;
    }

    result->size = 0;
    result->tuples = NULL;

    if (left->size != right->size) {
        return SUBTRACT_SHAPE_MISMATCH;
    }

    if (left->size > SIZE_MAX / sizeof(*result->tuples)) {
        return SUBTRACT_ALLOCATION_FAILURE;
    }

    if (left->size > 0) {
        result->tuples = calloc(left->size, sizeof(*result->tuples));
        if (result->tuples == NULL) {
            return SUBTRACT_ALLOCATION_FAILURE;
        }
    }

    result->size = left->size;

    for (size_t i = 0; i < left->size; ++i) {
        const Tuple *left_tuple = &left->tuples[i];
        const Tuple *right_tuple = &right->tuples[i];
        Tuple *result_tuple = &result->tuples[i];

        if ((left_tuple->size > 0 && left_tuple->elements == NULL) ||
            (right_tuple->size > 0 && right_tuple->elements == NULL)) {
            free_nested_tuple(result);
            return SUBTRACT_INVALID_ARGUMENT;
        }

        if (left_tuple->size != right_tuple->size) {
            free_nested_tuple(result);
            return SUBTRACT_SHAPE_MISMATCH;
        }

        if (left_tuple->size > SIZE_MAX / sizeof(*result_tuple->elements)) {
            free_nested_tuple(result);
            return SUBTRACT_ALLOCATION_FAILURE;
        }

        if (left_tuple->size > 0) {
            result_tuple->elements =
                malloc(left_tuple->size * sizeof(*result_tuple->elements));
            if (result_tuple->elements == NULL) {
                free_nested_tuple(result);
                return SUBTRACT_ALLOCATION_FAILURE;
            }
        }

        result_tuple->size = left_tuple->size;

        for (size_t j = 0; j < left_tuple->size; ++j) {
            if (__builtin_sub_overflow(
                    left_tuple->elements[j],
                    right_tuple->elements[j],
                    &result_tuple->elements[j])) {
                free_nested_tuple(result);
                return SUBTRACT_OVERFLOW;
            }
        }
    }

    return SUBTRACT_SUCCESS;
}

static int print_nested_tuple(const NestedTuple *nested)
{
    if (nested == NULL || (nested->size > 0 && nested->tuples == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < nested->size; ++i) {
        const Tuple *tuple = &nested->tuples[i];

        if (tuple->size > 0 && tuple->elements == NULL) {
            return -1;
        }

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < tuple->size; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", tuple->elements[j]) < 0) {
                return -1;
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }
    }

    if (puts(")") == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int left_first[] = {10, 20, 30};
    int left_second[] = {40, 50};
    int right_first[] = {1, 2, 3};
    int right_second[] = {4, 5};

    Tuple left_tuples[] = {
        {3, left_first},
        {2, left_second}
    };

    Tuple right_tuples[] = {
        {3, right_first},
        {2, right_second}
    };

    NestedTuple left = {2, left_tuples};
    NestedTuple right = {2, right_tuples};
    NestedTuple result = {0, NULL};

    SubtractResult status =
        subtract_nested_tuples(&left, &right, &result);

    if (status != SUBTRACT_SUCCESS) {
        fprintf(stderr, "Subtraction failed with error code %d\n", status);
        return EXIT_FAILURE;
    }

    if (print_nested_tuple(&result) != 0) {
        fprintf(stderr, "Output failed\n");
        free_nested_tuple(&result);
        return EXIT_FAILURE;
    }

    free_nested_tuple(&result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}