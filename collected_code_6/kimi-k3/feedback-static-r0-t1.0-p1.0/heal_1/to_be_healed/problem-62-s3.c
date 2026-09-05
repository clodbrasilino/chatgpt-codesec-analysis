#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_smallest(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return INT_MIN;
    }
    
    int smallest = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main(void) {
    int numbers[] = {42, 17, 8, 99, 23, 4};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(numbers)/sizeof(numbers[0])', assigned value is 6
     */
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = find_smallest(numbers, size);
    /* Possible weaknesses found:
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     *  Condition 'size==0' is always false
     */
    if (result != INT_MIN || size == 0) {
        printf("Smallest number: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}