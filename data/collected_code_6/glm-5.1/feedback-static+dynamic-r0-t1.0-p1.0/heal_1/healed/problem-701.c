#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_equilibrium_index(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    long long total_sum = 0;
    long long left_sum = 0;

    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    for (int i = 0; i < n; i++) {
        long long right_sum = total_sum - left_sum - arr[i];
        if (left_sum == right_sum) {
            return i;
        }
        left_sum += arr[i];
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || val > INT_MAX || val < INT_MIN) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int result = find_equilibrium_index(arr, n);
    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return 0;
}