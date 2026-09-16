#include <stdio.h>
#include <stdlib.h>

int find_max_occurrence(const int *arr, size_t size, int *max_item, int *max_count) {
    if (arr == NULL || max_item == NULL || max_count == NULL || size == 0) {
        return -1;
    }

    int *unique = malloc(size * sizeof(int));
    int *counts = malloc(size * sizeof(int));
    if (unique == NULL || counts == NULL) {
        free(unique);
        free(counts);
        return -1;
    }

    size_t unique_size = 0;
    for (size_t i = 0; i < size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_size; j++) {
            if (unique[j] == arr[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[unique_size] = arr[i];
            counts[unique_size] = 1;
            unique_size++;
        }
    }

    int max_idx = 0;
    for (size_t i = 1; i < unique_size; i++) {
        if (counts[i] > counts[max_idx]) {
            max_idx = i;
        }
    }

    *max_item = unique[max_idx];
    *max_count = counts[max_idx];

    free(unique);
    free(counts);
    return 0;
}

int main(void) {
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int max_item, max_count;

    if (find_max_occurrence(arr, size, &max_item, &max_count) == 0) {
        printf("Item with maximum occurrences: %d (occurs %d times)\n", max_item, max_count);
    } else {
        printf("Error: Invalid input\n");
    }

    return 0;
}