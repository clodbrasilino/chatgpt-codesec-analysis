#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_equilibrium_index(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    long long left_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum -= arr[i];
        if (left_sum == total_sum) {
            return i;
        }
        left_sum += arr[i];
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int equilibrium_idx = find_equilibrium_index(arr, n);
    printf("%d\n", equilibrium_idx);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}