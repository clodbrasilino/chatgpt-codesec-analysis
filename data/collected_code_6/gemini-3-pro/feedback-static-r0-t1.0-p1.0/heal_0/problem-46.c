#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_all_elements_unique(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return true; 
    }

    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    if (are_all_elements_unique(arr1, size1)) {
        printf("All elements in arr1 are unique.\n");
    } else {
        printf("arr1 contains duplicate elements.\n");
    }

    int arr2[] = {1, 2, 3, 4, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (are_all_elements_unique(arr2, size2)) {
        printf("All elements in arr2 are unique.\n");
    } else {
        printf("arr2 contains duplicate elements.\n");
    }

    return EXIT_SUCCESS;
}