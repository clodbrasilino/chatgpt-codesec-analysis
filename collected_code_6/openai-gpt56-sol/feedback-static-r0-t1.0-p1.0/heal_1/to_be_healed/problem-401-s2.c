#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
        if (left->tuples[i].length != right->tuples[i].length) {
            free_nested_tuple(result);
            return -1;
        }

        size_t length = left->tuples[i].length;
        result->tuples[i].length = length;

        if (length == 0) {
            continue;
        }

        if (left->tuples[i].elements == NULL ||
            right->tuples[i].elements == NULL ||
            length > SIZE_MAX / sizeof(*result->tuples[i].elements)) {
            free_nested_tuple(result);
            return -1;
        }

        result->tuples[i].elements = malloc(
            length * sizeof(*result->tuples[i].elements));

        if (result->tuples[i].elements == NULL) {
            free_nested_tuple(result);
            return -1;
        }

        for (size_t j = 0; j < length; ++j) {
            int a = left->tuples[i].elements[j];
            int b = right->tuples[i].elements[j];

            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'INT_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             */
            if ((b > 0 && a > INT_MAX - b) ||
                /* Possible weaknesses found:
                 *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
                 *  'INT_MIN' undeclared (first use in this function)
                 *  use of undeclared identifier 'INT_MIN'
                 */
                (b < 0 && a < INT_MIN - b)) {
                free_nested_tuple(result);
                return -1;
            }

            result->tuples[i].elements[j] = a + b;
        }
    }

    return 0;
}

static int print_nested_tuple(const MutableNestedTuple *nested)
{
    if (nested == NULL || (nested->length > 0 && nested->tuples == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < nested->length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < nested->tuples[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", nested->tuples[i].elements[j]) < 0) {
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