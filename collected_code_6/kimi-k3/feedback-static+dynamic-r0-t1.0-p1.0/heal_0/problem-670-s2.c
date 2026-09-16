#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_decreasing(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return false;
    }
    
    for (size_t i = 1; i < size; i++) {
        if (arr[i] >= arr[i - 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    size_t size;
    
    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%zu", &size) != 1 || size == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int *arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Enter %zu integers: ", size) < 0) {
        free(arr);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    if (is_decreasing(arr, size)) {
        printf("The sequence has a decreasing trend.\n");
    } else {
        printf("The sequence does not have a decreasing trend.\n");
    }
    
    free(arr);
    return EXIT_SUCCESS;
}