#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isSubset(const int* arr1, size_t size1, const int* arr2, size_t size2) {
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (size2 > size1) {
        return false;
    }

    for (size_t i = 0; i < size2; i++) {
        bool found = false;
        for (size_t j = 0; j < size1; j++) {
            if (arr2[i] == arr1[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (isSubset(arr1, size1, arr2, size2)) {
        printf("arr2 is a subset of arr1\n");
    } else {
        printf("arr2 is not a subset of arr1\n");
    }

    int arr3[] = {11, 3, 7, 1, 10};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    if (isSubset(arr1, size1, arr3, size3)) {
        printf("arr3 is a subset of arr1\n");
    } else {
        printf("arr3 is not a subset of arr1\n");
    }

    return EXIT_SUCCESS;
}