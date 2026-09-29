#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t length;
    int *elements;
} Tuple;

static bool contains(const int *elements, size_t length, int value)
{
    for (size_t i = 0; i < length; ++i) {
        if (elements[i] == value) {
            return true;
        }
    }

    return false;
}

static int compare_integers(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

bool find_tuple_intersection(const Tuple *tuples, size_t tuple_count,
                             Tuple *result)
{
    if (result == NULL) {
        return false;
    }

    result->length = 0;
    result->elements = NULL;

    if (tuple_count == 0) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].length > 0 && tuples[i].elements == NULL) {
            return false;
        }
    }

    if (tuples[0].length == 0) {
        return true;
    }

    if (tuples[0].length > SIZE_MAX / sizeof(*result->elements)) {
        return false;
    }

    int *intersection = malloc(tuples[0].length * sizeof(*intersection));
    if (intersection == NULL) {
        return false;
    }

    size_t intersection_length = 0;

    for (size_t i = 0; i < tuples[0].length; ++i) {
        const int value = tuples[0].elements[i];

        if (contains(intersection, intersection_length, value)) {
            continue;
        }

        bool present_in_all = true;

        for (size_t j = 1; j < tuple_count; ++j) {
            if (!contains(tuples[j].elements, tuples[j].length, value)) {
                present_in_all = false;
                break;
            }
        }

        if (present_in_all) {
            intersection[intersection_length++] = value;
        }
    }

    if (intersection_length == 0) {
        free(intersection);
        intersection = NULL;
    } else {
        qsort(intersection, intersection_length, sizeof(*intersection),
              compare_integers);
    }

    result->elements = intersection;
    result->length = intersection_length;
    return true;
}

int main(void)
{
    size_t tuple_count = 0;
    Tuple *tuples = NULL;
    Tuple intersection = {0, NULL};
    int status = EXIT_FAILURE;

    if (scanf("%zu", &tuple_count) != 1) {
        fputs("Invalid tuple count\n", stderr);
        goto cleanup;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        goto cleanup;
    }

    if (tuple_count > 0) {
        tuples = calloc(tuple_count, sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (scanf("%zu", &tuples[i].length) != 1) {
            fputs("Invalid tuple length\n", stderr);
            goto cleanup;
        }

        if (tuples[i].length > SIZE_MAX / sizeof(*tuples[i].elements)) {
            fputs("Tuple length is too large\n", stderr);
            goto cleanup;
        }

        if (tuples[i].length > 0) {
            tuples[i].elements =
                malloc(tuples[i].length * sizeof(*tuples[i].elements));

            if (tuples[i].elements == NULL) {
                fputs("Memory allocation failed\n", stderr);
                goto cleanup;
            }
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (scanf("%d", &tuples[i].elements[j]) != 1) {
                fputs("Invalid tuple element\n", stderr);
                goto cleanup;
            }
        }
    }

    if (!find_tuple_intersection(tuples, tuple_count, &intersection)) {
        fputs("Unable to compute tuple intersection\n", stderr);
        goto cleanup;
    }

    if (putchar('(') == EOF) {
        goto cleanup;
    }

    for (size_t i = 0; i < intersection.length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            goto cleanup;
        }

        if (printf("%d", intersection.elements[i]) < 0) {
            goto cleanup;
        }
    }

    if (puts(")") == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(intersection.elements);

    if (tuples != NULL) {
        for (size_t i = 0; i < tuple_count; ++i) {
            free(tuples[i].elements);
        }
    }

    free(tuples);
    return status;
}