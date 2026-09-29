#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_absolute_differences(const int *arr, size_t size) {
    long long sum = 0;
    size_t i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            int diff = arr[i] - arr[j];
            sum += (diff > 0) ? (long long)diff : -(long long)diff;
        }
    }
    return sum;
}

int main(int argc, char * const * const argv) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    if (argc > 1) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0' || val < 0 || (unsigned long)val > SIZE_MAX) {
            fprintf(stderr, "Invalid size\n");
            return EXIT_FAILURE;
        }
        size = (size_t)val;
    }
    if (size == 0) {
        fprintf(stderr, "Array must not be empty\n");
        return EXIT_FAILURE;
    }
    if (size > sizeof(arr) / sizeof(arr[0])) {
        fprintf(stderr, "Size exceeds array bounds\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_absolute_differences(arr, size);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}