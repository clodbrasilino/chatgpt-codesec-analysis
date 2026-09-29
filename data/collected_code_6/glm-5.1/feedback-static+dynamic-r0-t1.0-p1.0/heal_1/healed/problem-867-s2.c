#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int min_to_even_sum(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    }

    return 1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN || endptr == argv[i + 1] || *endptr != '\0') {
            free(arr);
            return EXIT_FAILURE;
        }

        arr[i] = (int)val;
    }

    int result = min_to_even_sum(arr, size);

    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}