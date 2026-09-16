#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(const int *arr, size_t size, int *duplicate) {
    if (arr == NULL || duplicate == NULL) {
        return -1;
    }
    
    if (size == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                *duplicate = arr[i];
                return 1;
            }
        }
    }
    
    return 0;
}

int main(void) {
    int arr[] = {4, 2, 7, 8, 2, 9, 4, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int duplicate;
    int result;
    
    result = find_first_duplicate(arr, size, &duplicate);
    
    if (result == 1) {
        printf("First duplicate element: %d\n", duplicate);
    } else if (result == 0) {
        printf("No duplicate elements found.\n");
    } else {
        fprintf(stderr, "Error: Invalid input parameters.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}