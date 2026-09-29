#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int64_t sum_abs_diff_pairs(const int *arr, size_t n) {
    if (arr == NULL || n < 2) {
        return 0;
    }
    
    int64_t sum = 0;
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            int64_t diff = (int64_t)arr[i] - (int64_t)arr[j];
            sum += (diff < 0) ? -diff : diff;
        }
    }
    return sum;
}

int main(void) {
    int arr[] = {1, 4, 2, 8, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int64_t result = sum_abs_diff_pairs(arr, n);
    
    if (printf("Array: ") < 0) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (printf("\nSum of absolute differences: %lld\n", (long long)result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}