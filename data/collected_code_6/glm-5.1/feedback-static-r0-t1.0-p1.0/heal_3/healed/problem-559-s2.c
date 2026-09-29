#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_subarray_sum(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int current_sum = 0;

    for (size_t i = 0; i < n; i++) {
        current_sum += arr[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (current_sum < 0) {
            current_sum = 0;
        }
    }

    return max_sum;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <space_separated_integers>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t n = (size_t)(argc - 1);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer input\n");
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = max_subarray_sum(arr, n);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}