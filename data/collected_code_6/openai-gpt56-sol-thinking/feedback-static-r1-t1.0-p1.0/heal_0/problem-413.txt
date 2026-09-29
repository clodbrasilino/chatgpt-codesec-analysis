#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

typedef enum {
    EXTRACT_SUCCESS = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_INDEX_OUT_OF_RANGE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractResult;

static ExtractResult extract_nth_elements(
    const Tuple *tuples,
    size_t tuple_count,
    size_t index,
    int **output,
    size_t *output_count)
{
    int *values;
    size_t i;

    if (output == NULL || output_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *output = NULL;
    *output_count = 0;

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

    *output = values;
    *output_count = tuple_count;

    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};
    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    int *values = NULL;
    size_t value_count = 0;
    size_t i;
    ExtractResult result;

    result = extract_nth_elements(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        1,
        &values,
        &value_count
    );

    if (result != EXTRACT_SUCCESS) {
        fprintf(stderr, "Failed to extract tuple elements: error %d\n", result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < value_count; ++i) {
        printf("%d%s", values[i], i + 1 < value_count ? " " : "\n");
    }

    free(values);
    return EXIT_SUCCESS;
}