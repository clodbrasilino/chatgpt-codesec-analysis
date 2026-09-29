#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *elements;
    size_t size;
} TupleRecord;

int find_max_element(TupleRecord *records, size_t num_records, int *max_value) {
    if (records == NULL || max_value == NULL || num_records == 0) {
        return -1;
    }

    int initialized = 0;
    int current_max = 0;

    for (size_t i = 0; i < num_records; ++i) {
        if (records[i].elements == NULL || records[i].size == 0) {
            continue;
        }

        for (size_t j = 0; j < records[i].size; ++j) {
            if (!initialized || records[i].elements[j] > current_max) {
                current_max = records[i].elements[j];
                initialized = 1;
            }
        }
    }

    if (!initialized) {
        return -1;
    }

    *max_value = current_max;
    return 0;
}

int main(void) {
    int arr1[] = {3, 5, 1};
    int arr2[] = {7, 2};
    int arr3[] = {4, 9, 0, 6};

    TupleRecord records[] = {
        {arr1, sizeof(arr1) / sizeof(arr1[0])},
        {arr2, sizeof(arr2) / sizeof(arr2[0])},
        {arr3, sizeof(arr3) / sizeof(arr3[0])}
    };

    size_t num_records = sizeof(records) / sizeof(records[0]);
    int max_val;

    int result = find_max_element(records, num_records, &max_val);

    if (result == 0) {
        printf("%d\n", max_val);
    } else {
        printf("Invalid input or no valid elements found.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}