#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long find_remainder(const int *arr, size_t size, int n) {
    unsigned long long result = 1ULL % (unsigned long long)n;
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            fprintf(stderr, "Error\n");
            exit(EXIT_FAILURE);
        }
        result = (result * (unsigned long long)arr[i]) % (unsigned long long)n;
    }
    return result;
}

int main(int argc, char * const * argv) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;

    size_t size = (size_t)argc - 2;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    size_t i;
    for (i = 0; i < size; i++) {
        val = strtol(argv[i + 2], &endptr, 10);
        if (endptr == argv[i + 2] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    printf("%llu\n", find_remainder(arr, size, n));
    free(arr);
    return EXIT_SUCCESS;
}