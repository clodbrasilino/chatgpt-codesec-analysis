#include <stdio.h>
#include <stdlib.h>

int find_max_occurrence(const int *arr, size_t size, int *max_item, size_t *max_count) {
    if (arr == NULL || max_item == NULL || max_count == NULL || size == 0) {
        return -1;
    }

    *max_item = arr[0];
    *max_count = 1;

    for (size_t i = 0; i < size; i++) {
        size_t current_count = 1;
        
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                current_count++;
            }
        }

        if (current_count > *max_count) {
            *max_count = current_count;
            *max_item = arr[i];
        }
    }

    return 0;
}

int main(void) {
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int max_item = 0;
    size_t max_count = 0;

    if (find_max_occurrence(arr, size, &max_item, &max_count) == 0) {
        printf("Item with maximum occurrences: %d\n", max_item);
        printf("Number of occurrences: %zu\n", max_count);
    } else {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}