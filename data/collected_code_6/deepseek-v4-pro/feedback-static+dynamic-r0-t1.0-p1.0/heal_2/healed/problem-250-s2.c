#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_occurrences(const int *tuple, size_t size, int element) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }
    return count;
}

static int safe_atoi(const char *str, int *result) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }

    if (val < INT_MIN || val > INT_MAX) {
        return -1;
    }

    *result = (int)val;
    return 0;
}

int main(const int argc, char *const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <element> [tuple elements...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int element;
    if (safe_atoi(argv[1], &element) != 0) {
        fprintf(stderr, "Invalid element: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 2);

    if (size == 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    int *tuple = malloc(size * sizeof(int));
    if (tuple == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        if (safe_atoi(argv[i + 2], &tuple[i]) != 0) {
            fprintf(stderr, "Invalid tuple element: %s\n", argv[i + 2]);
            free(tuple);
            return EXIT_FAILURE;
        }
    }

    int count = count_occurrences(tuple, size, element);
    printf("%d\n", count);

    free(tuple);
    return EXIT_SUCCESS;
}