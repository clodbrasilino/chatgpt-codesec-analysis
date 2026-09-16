#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

typedef enum {
    EXTRACT_SUCCESS,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_OUT_OF_RANGE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

static ExtractStatus extract_nth_elements(
    const Tuple *tuples,
    size_t tuple_count,
    size_t n,
    int **result,
    size_t *result_count
) {
    int *extracted = NULL;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (n == 0) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (tuple_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (tuples == NULL || tuple_count > SIZE_MAX / sizeof(*extracted)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL || n > tuples[i].length) {
            return EXTRACT_OUT_OF_RANGE;
        }
    }

    extracted = malloc(tuple_count * sizeof(*extracted));
    if (extracted == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        extracted[i] = tuples[i].elements[n - 1];
    }

    *result = extracted;
    *result_count = tuple_count;

    return EXTRACT_SUCCESS;
}

int main(void) {
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};
    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    int *result = NULL;
    size_t result_count = 0;
    size_t i;
    ExtractStatus status;

    status = extract_nth_elements(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        2,
        &result,
        &result_count
    );

    if (status != EXTRACT_SUCCESS) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", result[i]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}