#include <stdio.h>
#include <stdbool.h>

bool areArraysEqual(const int *arr1, const int *arr2, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int arr1[] = {1, 2, 3, 4};
    const int arr2[] = {1, 2, 3, 4};
    const int arr3[] = {1, 2, 3, 5};

    size_t len = sizeof(arr1) / sizeof(arr1[0]);

    if (areArraysEqual(arr1, arr2, len)) {
        printf("Array 1 and Array 2 are equal.\n");
    } else {
        printf("Array 1 and Array 2 are not equal.\n");
    }

    if (areArraysEqual(arr1, arr3, len)) {
        printf("Array 1 and Array 3 are equal.\n");
    } else {
        printf("Array 1 and Array 3 are not equal.\n");
    }

    return 0;
}