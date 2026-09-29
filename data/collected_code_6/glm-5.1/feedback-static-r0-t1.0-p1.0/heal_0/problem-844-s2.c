#include <stdio.h>
#include <stdlib.h>

int find_kth_element(int *arr, size_t n, size_t k) {
    if (arr == NULL) {
        exit(EXIT_FAILURE);
    }
    if (k == 0 || k > n) {
        exit(EXIT_FAILURE);
    }
    size_t odd_count = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            odd_count++;
        }
    }
    if (k <= odd_count) {
        size_t current_odd = 0;
        for (size_t i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                current_odd++;
                if (current_odd == k) {
                    return arr[i];
                }
            }
        }
    } else {
        size_t target_even = k - odd_count;
        size_t current_even = 0;
        for (size_t i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                current_even++;
                if (current_even == target_even) {
                    return arr[i];
                }
            }
        }
    }
    exit(EXIT_FAILURE);
}

int main(void) {
    int arr[] = {1, 2, 4, 5, 7, 8, 9, 10};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 5;
    int result = find_kth_element(arr, n, k);
    printf("%d\n", result);
    return 0;
}