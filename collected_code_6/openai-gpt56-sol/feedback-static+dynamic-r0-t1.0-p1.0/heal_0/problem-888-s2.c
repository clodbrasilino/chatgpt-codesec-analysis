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

static int subtract_nested_tuples(const NestedTuple *left,
                                  const NestedTuple *right,
                                  NestedTuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->size != right->size) {
        return 0;
    }

    result->size = 0;
    result->tuples = NULL;

    if (left->size == 0) {
        return 1;
    }

    result->tuples = calloc(left->size, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        return 0;
    }

    result->size = left->size;

    for (size_t i = 0; i < left->size; ++i) {
        const Tuple *a = &left->tuples[i];
        const Tuple *b = &right->tuples[i];
        Tuple *out = &result->tuples[i];

        if (a->size != b->size ||
            (a->size > 0 && (a->elements == NULL || b->elements == NULL))) {
            return 0;
        }

        out->size = a->size;

        if (out->size == 0) {
            continue;
        }

        out->elements = malloc(out->size * sizeof(*out->elements));
        if (out->elements == NULL) {
            return 0;
        }

        for (size_t j = 0; j < out->size; ++j) {
            out->elements[j] = a->elements[j] - b->elements[j];
        }
    }

    return 1;
}

static void free_nested_tuple(NestedTuple *nested)
{
    if (nested == NULL) {
        return;
    }

    for (size_t i = 0; i < nested->size; ++i) {
        free(nested->tuples[i].elements);
        nested->tuples[i].elements = NULL;
        nested->tuples[i].size = 0;
    }

    free(nested->tuples);
    nested->tuples = NULL;
    nested->size = 0;
}

static int print_nested_tuple(const NestedTuple *nested)
{
    if (nested == NULL || (nested->size > 0 && nested->tuples == NULL)) {
        return 0;
    }

    if (putchar('(') == EOF) {
        return 0;
    }

    for (size_t i = 0; i < nested->size; ++i) {
        const Tuple *tuple = &nested->tuples[i];

        if (tuple->size > 0 && tuple->elements == NULL) {
            return 0;
        }

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (putchar('(') == EOF) {
            return 0;
        }

        for (size_t j = 0; j < tuple->size; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf("%d", tuple->elements[j]) < 0) {
                return 0;
            }
        }

        if (putchar(')') == EOF) {
            return 0;
        }
    }

    return fputs(")\n", stdout) != EOF;
}

int main(void)
{
    int left_first[] = {10, 20, 30};
    int left_second[] = {40, 50};
    int right_first[] = {1, 2, 3};
    int right_second[] = {4, 5};

    Tuple left_tuples[] = {
        {sizeof(left_first) / sizeof(left_first[0]), left_first},
        {sizeof(left_second) / sizeof(left_second[0]), left_second}
    };

    Tuple right_tuples[] = {
        {sizeof(right_first) / sizeof(right_first[0]), right_first},
        {sizeof(right_second) / sizeof(right_second[0]), right_second}
    };

    NestedTuple left = {
        sizeof(left_tuples) / sizeof(left_tuples[0]),
        left_tuples
    };

    NestedTuple right = {
        sizeof(right_tuples) / sizeof(right_tuples[0]),
        right_tuples
    };

    NestedTuple result = {0, NULL};
    int status = EXIT_FAILURE;

    if (!subtract_nested_tuples(&left, &right, &result)) {
        fputs("Failed to subtract nested tuples.\n", stderr);
        goto cleanup;
    }

    if (!print_nested_tuple(&result)) {
        fputs("Failed to print the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_nested_tuple(&result);
    return status;
}