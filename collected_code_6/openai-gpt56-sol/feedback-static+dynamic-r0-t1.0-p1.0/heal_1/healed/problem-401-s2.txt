#include <limits.h>
#include <stdint.h>
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

static void free_nested_tuple(MutableNestedTuple *nested)
{
    if (nested == NULL) {
        return;
    }

    for (size_t i = 0; i < nested->length; ++i) {
        free(nested->tuples[i].elements);
    }

    free(nested->tuples);
    nested->tuples = NULL;
    nested->length = 0;
}

static int add_nested_tuples(
    const NestedTuple *left,
    const NestedTuple *right,
    MutableNestedTuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->length != right->length) {
        return -1;
    }

    result->tuples = NULL;
    result->length = 0;

    if (left->length == 0) {
        return 0;
    }

    if (left->tuples == NULL || right->tuples == NULL ||
        left->length > SIZE_MAX / sizeof(*result->tuples)) {
        return -1;
    }

    result->tuples = calloc(left->length, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        return -1;
    }

    result->length = left->length;

    for (size_t i = 0; i < left->length; ++i) {
        const Tuple *left_tuple = &left->tuples[i];
        const Tuple *right_tuple = &right->tuples[i];
        MutableTuple *output_tuple = &result->tuples[i];

        if (left_tuple->length != right_tuple->length) {
            free_nested_tuple(result);
            return -1;
        }

        output_tuple->length = left_tuple->length;

        if (output_tuple->length == 0) {
            continue;
        }

        if (left_tuple->elements == NULL ||
            right_tuple->elements == NULL ||
            output_tuple->length > SIZE_MAX / sizeof(*output_tuple->elements)) {
            free_nested_tuple(result);
            return -1;
        }

        output_tuple->elements =
            malloc(output_tuple->length * sizeof(*output_tuple->elements));

        if (output_tuple->elements == NULL) {
            free_nested_tuple(result);
            return -1;
        }

        for (size_t j = 0; j < output_tuple->length; ++j) {
            int a = left_tuple->elements[j];
            int b = right_tuple->elements[j];

            if ((b > 0 && a > INT_MAX - b) ||
                (b < 0 && a < INT_MIN - b)) {
                free_nested_tuple(result);
                return -1;
            }

            output_tuple->elements[j] = a + b;
        }
    }

    return 0;
}

static int print_nested_tuple(const MutableNestedTuple *nested)
{
    if (nested == NULL ||
        (nested->length > 0 && nested->tuples == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < nested->length; ++i) {
        const MutableTuple *tuple = &nested->tuples[i];

        if (tuple->length > 0 && tuple->elements == NULL) {
            return -1;
        }

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < tuple->length; ++j) {
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

    return fputs(")\n", stdout) == EOF ? -1 : 0;
}

int main(void)
{
    const int left_values_1[] = {1, 2, 3};
    const int left_values_2[] = {4, 5};
    const int right_values_1[] = {6, 7, 8};
    const int right_values_2[] = {9, 10};

    const Tuple left_tuples[] = {
        {left_values_1, sizeof(left_values_1) / sizeof(left_values_1[0])},
        {left_values_2, sizeof(left_values_2) / sizeof(left_values_2[0])}
    };

    const Tuple right_tuples[] = {
        {right_values_1, sizeof(right_values_1) / sizeof(right_values_1[0])},
        {right_values_2, sizeof(right_values_2) / sizeof(right_values_2[0])}
    };

    const NestedTuple left = {
        left_tuples,
        sizeof(left_tuples) / sizeof(left_tuples[0])
    };

    const NestedTuple right = {
        right_tuples,
        sizeof(right_tuples) / sizeof(right_tuples[0])
    };

    MutableNestedTuple result = {NULL, 0};

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