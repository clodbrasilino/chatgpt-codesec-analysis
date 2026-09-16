#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(int *array, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= array[i];
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <numbers...>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Integer overflow for argument %s\n", argv[i + 1]);
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int odd_occurrence = find_odd_occurrence(array, size);
    printf("%d\n", odd_occurrence);

    free(array);
    return EXIT_SUCCESS;
}