#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_smallest_frequency(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int smallest = array[0];
    int frequency = 1;

    for (size_t i = 1; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            frequency = 1;
        } else if (array[i] == smallest) {
            frequency++;
        }
    }

    return frequency;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int frequency = find_smallest_frequency(array, size);
    printf("%d\n", frequency);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}