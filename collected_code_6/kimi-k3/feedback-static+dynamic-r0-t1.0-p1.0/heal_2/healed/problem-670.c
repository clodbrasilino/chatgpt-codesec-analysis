#include <stdio.h>
#include <stdlib.h>

int has_decreasing_trend(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 1;
    }
    for (size_t i = 1; i < size; i++) {
        if (arr[i] >= arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    size_t size;
    if (scanf("%zu", &size) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    printf("%s\n", has_decreasing_trend(arr, size) ? "True" : "False");
    free(arr);
    return EXIT_SUCCESS;
}