#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int find_first_duplicate(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return arr[i];
            }
        }
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
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

    int result = find_first_duplicate(arr, size);

    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}