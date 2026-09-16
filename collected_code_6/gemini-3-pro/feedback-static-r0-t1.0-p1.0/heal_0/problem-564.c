#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    if (val_a < val_b) {
        return -1;
    }
    if (val_a > val_b) {
        return 1;
    }
    return 0;
}

size_t count_unequal_pairs(int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 0;
    }

    qsort(arr, size, sizeof(int), compare_ints);

    size_t total_pairs = (size * (size - 1)) / 2;
    size_t equal_pairs = 0;
    size_t current_count = 1;

    for (size_t i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            current_count++;
        } else {
            if (current_count > 1) {
                equal_pairs += (current_count * (current_count - 1)) / 2;
            }
            current_count = 1;
        }
    }
    
    if (current_count > 1) {
        equal_pairs += (current_count * (current_count - 1)) / 2;
    }

    return total_pairs - equal_pairs;
}

int main(void) {
    int arr[] = {1, 2, 3, 1, 2, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t unequal_pairs = count_unequal_pairs(arr, size);

    printf("%zu\n", unequal_pairs);

    return 0;
}