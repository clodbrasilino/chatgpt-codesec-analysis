#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_first_odd(const int *numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            return numbers[i];
        }
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    size_t count = argc - 1;
    int *numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid input: %s\n", argv[i + 1]);
            free(numbers);
            return 1;
        }
        numbers[i] = (int)val;
    }

    int result = find_first_odd(numbers, count);
    if (result == -1) {
        printf("No odd number found\n");
    } else {
        printf("%d\n", result);
    }

    free(numbers);
    return 0;
}