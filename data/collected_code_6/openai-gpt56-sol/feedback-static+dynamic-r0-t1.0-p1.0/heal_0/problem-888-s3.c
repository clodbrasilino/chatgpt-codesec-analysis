#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    const long long *elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t length;
} NestedTuple;

static int subtract_nested_tuples(const NestedTuple *left,
                                  const NestedTuple *right,
                                  NestedTuple *result)
{
    size_t i;
    size_t j;

    if (left == NULL || right == NULL || result == NULL ||
        left->length != right->length) {
        return 0;
    }

    result->tuples = NULL;
    result->length = 0;

    if (left->length == 0) {
        return 1;
    }

    result->tuples = calloc(left->length, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        return 0;
    }

    result->length = left->length;

    for (i = 0; i < left->length; ++i) {
        long long *elements;

        if (left->tuples[i].length != right->tuples[i].length ||
            (left->tuples[i].length > 0 &&
             (left->tuples[i].elements == NULL ||
              right->tuples[i].elements == NULL))) {
            goto failure;
        }

        result->tuples[i].length = left->tuples[i].length;

        if (left->tuples[i].length == 0) {
            result->tuples[i].elements = NULL;
            continue;
        }

        elements = malloc(left->tuples[i].length * sizeof(*elements));
        if (elements == NULL) {
            goto failure;
        }

        for (j = 0; j < left->tuples[i].length; ++j) {
            elements[j] = left->tuples[i].elements[j] -
                          right->tuples[i].elements[j];
        }

        result->tuples[i].elements = elements;
    }

    return 1;

failure:
    for (i = 0; i < result->length; ++i) {
        free((void *)result->tuples[i].elements);
    }
    free(result->tuples);
    result->tuples = NULL;
    result->length = 0;
    return 0;
}

static void free_nested_tuple(NestedTuple *nested)
{
    size_t i;

    if (nested == NULL) {
        return;
    }

    for (i = 0; i < nested->length; ++i) {
        free((void *)nested->tuples[i].elements);
    }

    free(nested->tuples);
    nested->tuples = NULL;
    nested->length = 0;
}

static void print_nested_tuple(const NestedTuple *nested)
{
    size_t i;
    size_t j;

    if (nested == NULL) {
        return;
    }

    putchar('(');
    for (i = 0; i < nested->length; ++i) {
        putchar('(');
        for (j = 0; j < nested->tuples[i].length; ++j) {
            printf("%lld", nested->tuples[i].elements[j]);
            if (j + 1 < nested->tuples[i].length) {
                printf(", ");
            }
        }
        putchar(')');
        if (i + 1 < nested->length) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const long long left_first[] = {10, 20, 30};
    const long long left_second[] = {40, 50};
    const long long right_first[] = {1, 2, 3};
    const long long right_second[] = {4, 5};

    const Tuple left_tuples[] = {
        {left_first, sizeof(left_first) / sizeof(left_first[0])},
        {left_second, sizeof(left_second) / sizeof(left_second[0])}
    };

    const Tuple right_tuples[] = {
        {right_first, sizeof(right_first) / sizeof(right_first[0])},
        {right_second, sizeof(right_second) / sizeof(right_second[0])}
    };

    const NestedTuple left = {
        (Tuple *)left_tuples,
        sizeof(left_tuples) / sizeof(left_tuples[0])
    };

    const NestedTuple right = {
        (Tuple *)right_tuples,
        sizeof(right_tuples) / sizeof(right_tuples[0])
    };

    NestedTuple result = {NULL, 0};

    if (!subtract_nested_tuples(&left, &right, &result)) {
        fprintf(stderr, "Unable to subtract nested tuples.\n");
        return EXIT_FAILURE;
    }

    print_nested_tuple(&result);
    free_nested_tuple(&result);

    return EXIT_SUCCESS;
}