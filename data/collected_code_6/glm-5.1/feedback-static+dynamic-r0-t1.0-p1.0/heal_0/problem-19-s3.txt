#include <stdio.h>
#include <stdlib.h>

int contains_duplicate(int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 0;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    unsigned long long range = (unsigned long long)max_val - (unsigned long long)min_val + 1;

    if (range > 100000000ULL || range < size) {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = i + 1; j < size; j++) {
                if (arr[i] == arr[j]) {
                    return 1;
                }
            }
        }
        return 0;
    }

    size_t alloc_size = sizeof(int) * range;
    if (alloc_size / sizeof(int) != range) {
        return 0;
    }

    int *counts = (int *)malloc(alloc_size);
    if (counts == NULL) {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = i + 1; j < size; j++) {
                if (arr[i] == arr[j]) {
                    return 1;
                }
            }
        }
        return 0;
    }

    for (unsigned long long i = 0; i < range; i++) {
        counts[i] = 0;
    }

    for (size_t i = 0; i < size; i++) {
        unsigned long long index = (unsigned long long)arr[i] - (unsigned long long)min_val;
        if (counts[index] == 1) {
            free(counts);
            return 1;
        }
        counts[index] = 1;
    }

    free(counts);
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", contains_duplicate(arr1, size1));

    int arr2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", contains_duplicate(arr2, size2));

    int arr3[] = {10};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", contains_duplicate(arr3, size3));

    printf("%d\n", contains_duplicate(NULL, size3));

    return 0;
}