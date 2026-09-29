#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_subarray(const int *arr1, size_t len1, const int *arr2, size_t len2) {
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (len2 > len1) {
        return false;
    }

    if (len2 == 0) {
        return true;
    }

    size_t limit = len1 - len2;

    for (size_t i = 0; i <= limit; i++) {
        bool match = true;
        for (size_t j = 0; j < len2; j++) {
            if (arr1[i + j] != arr2[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const int arr1[] = {1, 2, 3, 4, 5, 6};
    const int arr2[] = {3, 4, 5};
    const int arr3[] = {1, 2, 3};
    const int arr4[] = {5, 6, 7};
    const int arr5[] = {0};

    if (is_subarray(arr1, 6, arr2, 3)) {
        printf("arr2 is a subarray of arr1\n");
    } else {
        printf("arr2 is not a subarray of arr1\n");
    }

    if (is_subarray(arr1, 6, arr3, 3)) {
        printf("arr3 is a subarray of arr1\n");
    } else {
        printf("arr3 is not a subarray of arr1\n");
    }

    if (is_subarray(arr1, 6, arr4, 3)) {
        printf("arr4 is a subarray of arr1\n");
    } else {
        printf("arr4 is not a subarray of arr1\n");
    }

    if (is_subarray(arr1, 6, arr5, 0)) {
        printf("arr5 is a subarray of arr1\n");
    } else {
        printf("arr5 is not a subarray of arr1\n");
    }

    is_subarray(NULL, 6, arr2, 3);

    return 0;
}