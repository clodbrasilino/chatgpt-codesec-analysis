#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_all_elements_unique(const int *array, size_t length) {
    if (array == NULL || length == 0) {
        return true; 
    }

    for (size_t i = 0; i < length - 1; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (array[i] == array[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {1, 2, 3, 4, 1};
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    if (are_all_elements_unique(arr1, len1)) {
        printf("Array 1 has all unique elements.\n");
    } else {
        printf("Array 1 has duplicate elements.\n");
    }

    if (are_all_elements_unique(arr2, len2)) {
        printf("Array 2 has all unique elements.\n");
    } else {
        printf("Array 2 has duplicate elements.\n");
    }

    return 0;
}