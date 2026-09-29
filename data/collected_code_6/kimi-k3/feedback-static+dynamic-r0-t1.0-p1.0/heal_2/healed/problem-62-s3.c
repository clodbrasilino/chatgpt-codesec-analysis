#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_smallest(const int *arr, size_t size, int *result) {
    if (arr == NULL || size == 0 || result == NULL) {
        return -1;
    }
    
    int smallest = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    *result = smallest;
    return 0;
}

int main(void) {
    int numbers[] = {42, 17, 8, 99, 23, 4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result;
    if (find_smallest(numbers, size, &result) == 0) {
        printf("Smallest number: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}