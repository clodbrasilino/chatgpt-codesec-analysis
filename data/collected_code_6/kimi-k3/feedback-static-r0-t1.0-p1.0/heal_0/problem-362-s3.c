#include <stdio.h>
#include <stdlib.h>

int find_max_occurrence(const int *arr, size_t size, size_t *max_count) {
    if (arr == NULL || size == 0 || max_count == NULL) {
        return -1;
    }

    int max_item = arr[0];
    *max_count = 1;

    for (size_t i = 0; i < size; i++) {
        size_t current_count = 0;
        for (size_t j = 0; j < size; j++) {
            if (arr[j] == arr[i]) {
                current_count++;
            }
        }
        if (current_count > *max_count) {
            *max_count = current_count;
            max_item = arr[i];
        }
    }

    return max_item;
}

int main(void) {
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t max_count = 0;

    int result = find_max_occurrence(arr, size, &max_count);

    if (result != -1) {
        printf("Item with maximum occurrences: %d\n", result);
        printf("Number of occurrences: %zu\n", max_count);
    } else {
        fprintf(stderr, "Error: Invalid input or empty array\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}