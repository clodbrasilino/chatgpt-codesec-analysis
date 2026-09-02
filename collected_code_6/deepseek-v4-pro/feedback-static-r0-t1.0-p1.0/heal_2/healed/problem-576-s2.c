#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_subarray(const int *arr1, size_t len1, const int *arr2, size_t len2) {
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }
    if (len2 == 0) {
        return true;
    }
    if (len1 < len2) {
        return false;
    }

    for (size_t i = 0; i <= len1 - len2; i++) {
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
    int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    int arr2[] = {3, 4, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    if (is_subarray(arr1, len1, arr2, len2)) {
        printf("arr2 is a subarray of arr1\n");
    } else {
        printf("arr2 is not a subarray of arr1\n");
    }

    int arr3[] = {4, 5, 6, 8};
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    if (is_subarray(arr1, len1, arr3, len3)) {
        printf("arr3 is a subarray of arr1\n");
    } else {
        printf("arr3 is not a subarray of arr1\n");
    }

    const int arr4[] = {};
    if (is_subarray(arr1, len1, arr4, 0)) {
        printf("empty array is a subarray of arr1\n");
    }

    return 0;
}