#include <stdio.h>
#include <stdlib.h>

int count_unequal_pairs(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 0;
    }
    
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] != arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = count_unequal_pairs(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}