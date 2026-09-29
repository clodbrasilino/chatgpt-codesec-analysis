#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} TupleRecord;

typedef enum {
    EXTRACTION_SUCCESS,
    EXTRACTION_INVALID_ARGUMENT,
    EXTRACTION_EMPTY_TUPLE,
    EXTRACTION_ALLOCATION_FAILURE
} ExtractionStatus;

ExtractionStatus extract_rear_elements(const TupleRecord *records,
                                       size_t record_count,
                                       int **rear_elements,
                                       size_t *rear_count)
{
    int *result;
    size_t i;

    if (rear_elements == NULL || rear_count == NULL) {
        return EXTRACTION_INVALID_ARGUMENT;
    }

    *rear_elements = NULL;
    *rear_count = 0;

    if (record_count == 0) {
        return EXTRACTION_SUCCESS;
    }

    if (records == NULL || record_count > SIZE_MAX / sizeof(*result)) {
        return EXTRACTION_INVALID_ARGUMENT;
    }

    for (i = 0; i < record_count; ++i) {
        if (records[i].elements == NULL) {
            return EXTRACTION_INVALID_ARGUMENT;
        }

        if (records[i].length == 0) {
            return EXTRACTION_EMPTY_TUPLE;
        }
    }

    result = malloc(record_count * sizeof(*result));
    if (result == NULL) {
        return EXTRACTION_ALLOCATION_FAILURE;
    }

    for (i = 0; i < record_count; ++i) {
        result[i] = records[i].elements[records[i].length - 1];
    }

    *rear_elements = result;
    *rear_count = record_count;

    return EXTRACTION_SUCCESS;
}

int main(void)
{
    const int tuple1[] = {1, 2, 3};
    const int tuple2[] = {4, 5};
    const int tuple3[] = {6, 7, 8, 9};
    const TupleRecord records[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };
    const size_t record_count = sizeof(records) / sizeof(records[0]);
    int *rear_elements = NULL;
    size_t rear_count = 0;
    size_t i;
    ExtractionStatus status;

    status = extract_rear_elements(records, record_count,
                                   &rear_elements, &rear_count);
    if (status != EXTRACTION_SUCCESS) {
        fprintf(stderr, "Rear element extraction failed with status %d\n",
                (int)status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < rear_count; ++i) {
        printf("%d%s", rear_elements[i], i + 1 < rear_count ? " " : "\n");
    }

    free(rear_elements);
    return EXIT_SUCCESS;
}