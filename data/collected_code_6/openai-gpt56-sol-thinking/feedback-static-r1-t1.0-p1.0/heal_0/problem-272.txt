#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

bool extract_rear_elements(const Tuple *records, size_t record_count,
                           int **rear_elements, size_t *rear_count)
{
    int *result;

    if (rear_elements == NULL || rear_count == NULL) {
        return false;
    }

    *rear_elements = NULL;
    *rear_count = 0;

    if (record_count == 0) {
        return true;
    }

    if (records == NULL || record_count > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    for (size_t i = 0; i < record_count; ++i) {
        if (records[i].elements == NULL || records[i].length == 0) {
            return false;
        }
    }

    result = malloc(record_count * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < record_count; ++i) {
        result[i] = records[i].elements[records[i].length - 1];
    }

    *rear_elements = result;
    *rear_count = record_count;
    return true;
}

int main(void)
{
    const int tuple1[] = {1, 2, 3};
    const int tuple2[] = {4, 5};
    const int tuple3[] = {6, 7, 8, 9};
    const Tuple records[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };
    int *rear_elements = NULL;
    size_t rear_count = 0;

    if (!extract_rear_elements(
            records,
            sizeof(records) / sizeof(records[0]),
            &rear_elements,
            &rear_count)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rear_count; ++i) {
        if (printf("%d%s", rear_elements[i],
                   i + 1 < rear_count ? " " : "\n") < 0) {
            free(rear_elements);
            return EXIT_FAILURE;
        }
    }

    free(rear_elements);
    return EXIT_SUCCESS;
}