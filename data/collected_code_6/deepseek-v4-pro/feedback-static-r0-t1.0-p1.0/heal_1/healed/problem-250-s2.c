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

static int safe_atoi(const char *str, int *value) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    *value = (int)val;
    return 1;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <element> [tuple elements...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int element;
    if (!safe_atoi(argv[1], &element)) {
        fprintf(stderr, "Invalid element value: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 2;

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
        if (!safe_atoi(argv[i + 2], &tuple[i])) {
            fprintf(stderr, "Invalid tuple value: %s\n", argv[i + 2]);
            free(tuple);
            return EXIT_FAILURE;
        }
    }

    int count = count_occurrences(tuple, size, element);
    printf("%d\n", count);

    free(tuple);
    return EXIT_SUCCESS;
}