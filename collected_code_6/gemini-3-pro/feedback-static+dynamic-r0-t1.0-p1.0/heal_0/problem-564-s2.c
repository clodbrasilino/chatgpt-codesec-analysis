#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

size_t count_unequal_pairs(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[i] != arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    size_t unequal_pairs = count_unequal_pairs(arr, size);
    
    if (printf("%zu\n", unequal_pairs) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}