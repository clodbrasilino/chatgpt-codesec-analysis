#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool find_smallest(const int *arr, size_t size, int *result) {
    if (arr == NULL || size == 0 || result == NULL) {
        return false;
    }
    
    int smallest = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    
    *result = smallest;
    return true;
}

int main(void) {
    int numbers[] = {42, 17, 8, 99, 23, 5, 76};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    
    if (!find_smallest(numbers, count, &result)) {
        fprintf(stderr, "Error: empty or invalid array\n");
        return EXIT_FAILURE;
    }
    
    printf("Smallest number: %d\n", result);
    return EXIT_SUCCESS;
}