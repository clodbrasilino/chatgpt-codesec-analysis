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
    EXTRACT_EMPTY_TUPLE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

static ExtractStatus extract_rear_elements(
    const Tuple *records,
    size_t record_count,
    int **rear_elements,
    size_t *rear_count)
{
    int *result;
    size_t i;

    if (rear_elements == NULL || rear_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *rear_elements = NULL;
    *rear_count = 0;

    if (record_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (records == NULL || record_count > SIZE_MAX / sizeof(*result)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < record_count; ++i) {
        if (records[i].elements == NULL || records[i].length == 0) {
            return EXTRACT_EMPTY_TUPLE;
        }
    }

    result = malloc(record_count * sizeof(*result));
    if (result == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (i = 0; i < record_count; ++i) {
        result[i] = records[i].elements[records[i].length - 1];
    }

    *rear_elements = result;
    *rear_count = record_count;

    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const Tuple records[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    int *rear_elements = NULL;
    size_t rear_count = 0;
    size_t i;
    ExtractStatus status;

    status = extract_rear_elements(
        records,
        sizeof(records) / sizeof(records[0]),
        &rear_elements,
        &rear_count
    );

    if (status != EXTRACT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (putchar('[') == EOF) {
        free(rear_elements);
        return EXIT_FAILURE;
    }

    for (i = 0; i < rear_count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            free(rear_elements);
            return EXIT_FAILURE;
        }

        if (printf("%d", rear_elements[i]) < 0) {
            free(rear_elements);
            return EXIT_FAILURE;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        free(rear_elements);
        return EXIT_FAILURE;
    }

    free(rear_elements);
    return EXIT_SUCCESS;
}