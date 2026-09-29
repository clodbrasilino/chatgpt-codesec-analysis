#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *array, size_t size, size_t k) {
    if (array == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (size == 0 || k < 1 || k > size) {
        exit(EXIT_FAILURE);
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (k <= odd_count) {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            if (array[i] % 2 != 0) {
                count++;
                if (count == k) {
                    return array[i];
                }
            }
        }
    } else {
        size_t target = k - odd_count;
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            if (array[i] % 2 == 0) {
                count++;
                if (count == target) {
                    return array[i];
                }
            }
        }
    }

    exit(EXIT_FAILURE);
}

int main(void) {
    int arr[] = {1, 2, 4, 5, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k = 5;

    int result = find_kth_element(arr, size, k);
    printf("%d\n", result);

    return 0;
}