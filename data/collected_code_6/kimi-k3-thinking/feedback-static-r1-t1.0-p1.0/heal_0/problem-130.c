#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool find_max_frequency(const int *arr, size_t size, int *max_item, size_t *max_count)
{
    if (arr == NULL || max_item == NULL || max_count == NULL || size == 0) {
        return false;
    }

    size_t best_count = 0;
    int best_item = arr[0];

    for (size_t i = 0; i < size; i++) {
        size_t count = 0;
        for (size_t j = 0; j < size; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > best_count) {
            best_count = count;
            best_item = arr[i];
        }
    }

    *max_item = best_item;
    *max_count = best_count;
    return true;
}

int main(void)
{
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int max_item = 0;
    size_t max_count = 0;

    if (find_max_frequency(arr, size, &max_item, &max_count)) {
        printf("Item with maximum frequency: %d (occurs %zu times)\n", max_item, max_count);
    } else {
        fprintf(stderr, "Error: invalid input or empty list\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}