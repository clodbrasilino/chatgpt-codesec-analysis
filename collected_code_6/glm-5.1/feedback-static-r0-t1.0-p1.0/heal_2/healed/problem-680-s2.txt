#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool has_increasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL) {
        return false;
    }

    if (length <= 1) {
        return true;
    }

    for (size_t i = 0; i < length - 1; i++) {
        if (sequence[i] >= sequence[i + 1]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t length = argc - 1;
    int *sequence = malloc(length * sizeof(int));
    if (sequence == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(sequence);
            return EXIT_FAILURE;
        }
        sequence[i] = (int)val;
    }

    bool result = has_increasing_trend(sequence, length);
    printf("%s\n", result ? "Increasing" : "Not increasing");

    free(sequence);
    return EXIT_SUCCESS;
}