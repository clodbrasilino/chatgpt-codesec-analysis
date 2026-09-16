#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

typedef struct {
    const Tuple *tuples;
    size_t length;
} NestedTuple;

typedef struct {
    int *elements;
    size_t length;
} MutableTuple;

typedef struct {
    MutableTuple *tuples;
    size_t length;
} MutableNestedTuple;

static void free_nested_tuple(MutableNestedTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0U; i < tuple->length; ++i) {
        free(tuple->tuples[i].elements);
    }

    free(tuple->tuples);
    tuple->tuples = NULL;
    tuple->length = 0U;
}

static int add_nested_tuples(const NestedTuple *left,
                             const NestedTuple *right,
                             MutableNestedTuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->length != right->length) {
        return -1;
    }

    result->tuples = NULL;
    result->length = 0U;

    if (left->length == 0U) {
        return 0;
    }

    result->tuples = calloc(left->length, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        return -1;
    }

    result->length = left->length;

    for (size_t i = 0U; i < left->length; ++i) {
        if (left->tuples[i].length != right->tuples[i].length ||
            (left->tuples[i].length > 0U &&
             (left->tuples[i].elements == NULL ||
              right->tuples[i].elements == NULL))) {
            free_nested_tuple(result);
            return -1;
        }

        result->tuples[i].length = left->tuples[i].length;

        if (result->tuples[i].length == 0U) {
            continue;
        }

        result->tuples[i].elements =
            malloc(result->tuples[i].length * sizeof(*result->tuples[i].elements));
        if (result->tuples[i].elements == NULL) {
            free_nested_tuple(result);
            return -1;
        }

        for (size_t j = 0U; j < result->tuples[i].length; ++j) {
            result->tuples[i].elements[j] =
                left->tuples[i].elements[j] + right->tuples[i].elements[j];
        }
    }

    return 0;
}

static int print_nested_tuple(const MutableNestedTuple *tuple)
{
    if (tuple == NULL || (tuple->length > 0U && tuple->tuples == NULL)) {
        return -1;
    }

    if (printf("(") < 0) {
        return -1;
    }

    for (size_t i = 0U; i < tuple->length; ++i) {
        if (printf("(") < 0) {
            return -1;
        }

        for (size_t j = 0U; j < tuple->tuples[i].length; ++j) {
            if (printf("%d%s",
                       tuple->tuples[i].elements[j],
                       j + 1U < tuple->tuples[i].length ? ", " : "") < 0) {
                return -1;
            }
        }

        if (printf(")%s", i + 1U < tuple->length ? ", " : "") < 0) {
            return -1;
        }
    }

    return printf(")\n") < 0 ? -1 : 0;
}

int main(void)
{
    const int left_first[] = {1, 2, 3};
    const int left_second[] = {4, 5};
    const int right_first[] = {10, 20, 30};
    const int right_second[] = {40, 50};

    const Tuple left_tuples[] = {
        {left_first, sizeof(left_first) / sizeof(left_first[0])},
        {left_second, sizeof(left_second) / sizeof(left_second[0])}
    };

    const Tuple right_tuples[] = {
        {right_first, sizeof(right_first) / sizeof(right_first[0])},
        {right_second, sizeof(right_second) / sizeof(right_second[0])}
    };

    const NestedTuple left = {
        left_tuples,
        sizeof(left_tuples) / sizeof(left_tuples[0])
    };

    const NestedTuple right = {
        right_tuples,
        sizeof(right_tuples) / sizeof(right_tuples[0])
    };

    MutableNestedTuple result = {NULL, 0U};

    if (add_nested_tuples(&left, &right, &result) != 0) {
        fputs("Unable to add nested tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_nested_tuple(&result) != 0) {
        free_nested_tuple(&result);
        fputs("Unable to print the result.\n", stderr);
        return EXIT_FAILURE;
    }

    free_nested_tuple(&result);
    return EXIT_SUCCESS;
}