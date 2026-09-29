#include <stdio.h>
#include <stdlib.h>

int max_bitonic_sum(const int *arr, size_t n, int *error_flag);

int max_bitonic_sum(const int *arr, size_t n, int *error_flag) {
    if (arr == NULL || n == 0) {
        if (error_flag) {
            *error_flag = 1;
        }
        return 0;
    }

    if (error_flag) {
        *error_flag = 0;
    }

    int *inc = (int *)malloc(n * sizeof(int));
    if (inc == NULL) {
        if (error_flag) {
            *error_flag = 1;
        }
        return 0;
    }

    int *dec = (int *)malloc(n * sizeof(int));
    if (dec == NULL) {
        free(inc);
        if (error_flag) {
            *error_flag = 1;
        }
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        inc[i] = arr[i];
        dec[i] = arr[i];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + arr[i]) {
                inc[i] = inc[j] + arr[i];
            }
        }
    }

    for (size_t i = n - 1; i > 0; i--) {
        size_t idx = i - 1;
        for (size_t j = n - 1; j > idx; j--) {
            if (arr[idx] > arr[j] && dec[idx] < dec[j] + arr[idx]) {
                dec[idx] = dec[j] + arr[idx];
            }
        }
    }

    int max_sum = inc[0] + dec[0] - arr[0];
    for (size_t i = 1; i < n; i++) {
        int current_sum = inc[i] + dec[i] - arr[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    free(inc);
    free(dec);

    return max_sum;
}

int main(void) {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int error_flag = 0;

    int result = max_bitonic_sum(arr, n, &error_flag);
    
    if (error_flag) {
        fprintf(stderr, "Error: Invalid input or memory allocation failure.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}