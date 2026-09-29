#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool areArraysEqual(const int *arr1, const int *arr2, size_t size) {
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 3, 4, 6};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    if (areArraysEqual(arr1, arr2, size)) {
        printf("arr1 and arr2 are equal\n");
    } else {
        printf("arr1 and arr2 are not equal\n");
    }

    if (areArraysEqual(arr1, arr3, size)) {
        printf("arr1 and arr3 are equal\n");
    } else {
        printf("arr1 and arr3 are not equal\n");
    }

    return 0;
}