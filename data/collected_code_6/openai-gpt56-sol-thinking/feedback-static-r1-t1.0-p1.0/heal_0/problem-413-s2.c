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
    EXTRACT_INDEX_OUT_OF_RANGE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

static ExtractStatus extract_nth_elements(
    const Tuple *tuples,
    size_t tuple_count,
    size_t index,
    int **result,
    size_t *result_count
) {
    int *values;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (tuples == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL) {
            return EXTRACT_INVALID_ARGUMENT;
        }

        if (index >= tuples[i].length) {
            return EXTRACT_INDEX_OUT_OF_RANGE;
        }
    }

    if (tuple_count > SIZE_MAX / sizeof(*values)) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    values = malloc(tuple_count * sizeof(*values));
    if (values == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        values[i] = tuples[i].elements[index];
    }

    *result = values;
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
    const size_t index = 1;
    int *result = NULL;
    size_t result_count = 0;
    size_t i;
    ExtractStatus status;

    status = extract_nth_elements(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        index,
        &result,
        &result_count
    );

    if (status != EXTRACT_SUCCESS) {
        fprintf(stderr, "Unable to extract element: error %d\n", (int)status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        printf("%d%s", result[i], i + 1 < result_count ? " " : "\n");
    }

    free(result);
    return EXIT_SUCCESS;
}