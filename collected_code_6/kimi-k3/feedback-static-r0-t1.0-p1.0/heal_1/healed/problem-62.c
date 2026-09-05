#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int find_smallest(const int *arr, size_t size, bool *valid) {
    if (arr == NULL || size == 0) {
        *valid = false;
        return INT_MIN;
    }
    
    *valid = true;
    int smallest = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main(void) {
    int numbers[] = {34, 15, 88, 2, 47, 19};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    bool valid = false;
    int result = find_smallest(numbers, size, &valid);
    
    if (!valid) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Smallest number: %d\n", result);
    return EXIT_SUCCESS;
}