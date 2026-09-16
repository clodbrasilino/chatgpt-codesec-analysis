#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int extract_rear_elements(
    const int *records,
    size_t record_count,
    int **rear_elements
) {
    if (rear_elements == NULL) {
        return -1;
    }

    *rear_elements = NULL;

    if (record_count == 0) {
        return 0;
    }

    if (records == NULL || record_count > SIZE_MAX / sizeof(**rear_elements)) {
        return -1;
    }

    int *result = malloc(record_count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < record_count; ++i) {
        result[i] = records[i];
    }

    *rear_elements = result;
    return 0;
}

int main(void) {
    const int records[] = {10, 20, 30, 40};
    const size_t record_count = sizeof(records) / sizeof(records[0]);
    int *rear_elements = NULL;

    if (extract_rear_elements(records, record_count, &rear_elements) != 0) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < record_count; ++i) {
        printf("%d%s",
               rear_elements[i],
               i + 1 == record_count ? "\n" : " ");
    }

    free(rear_elements);
    return EXIT_SUCCESS;
}