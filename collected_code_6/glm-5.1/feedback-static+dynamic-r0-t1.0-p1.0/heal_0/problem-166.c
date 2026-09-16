#include <stdio.h>
#include <stdlib.h>

long long count_even_xor_pairs(int *arr, int n) {
    if (n < 2) {
        return 0;
    }

    int even_count = 0;
    int odd_count = 0;

    for (int i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    long long even_pairs = (long long)even_count * (even_count - 1) / 2;
    long long odd_pairs = (long long)odd_count * (odd_count - 1) / 2;

    return even_pairs + odd_pairs;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
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
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer input: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    long long result = count_even_xor_pairs(arr, n);
    printf("%lld\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}