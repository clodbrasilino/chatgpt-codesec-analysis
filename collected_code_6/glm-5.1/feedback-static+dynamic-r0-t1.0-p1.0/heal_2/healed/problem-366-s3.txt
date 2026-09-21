#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int largest_product(const int *arr, int size) {
    if (size < 2) {
        return 0;
    }

    int max_product = arr[0] * arr[1];

    for (int i = 1; i < size - 1; i++) {
        int current_product = arr[i] * arr[i + 1];
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}

int main(int argc, char * const * const argv) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);

        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(arr);
            return EXIT_FAILURE;
        }

        arr[i] = (int)val;
    }

    int result = largest_product(arr, size);

    printf("%d\n", result);

    free(arr);

    return EXIT_SUCCESS;
}