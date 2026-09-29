#include <stdio.h>
#include <stdlib.h>

int are_arrays_equal(const int *arr1, size_t len1, const int *arr2, size_t len2) {
    if (arr1 == NULL && arr2 == NULL) {
        return 1;
    }
    if (arr1 == NULL || arr2 == NULL) {
        return 0;
    }
    if (len1 != len2) {
        return 0;
    }
    for (size_t i = 0; i < len1; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 3, 4};
    int arr4[] = {1, 2, 3, 4, 6};

    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t len4 = sizeof(arr4) / sizeof(arr4[0]);

    int result1 = are_arrays_equal(arr1, len1, arr2, len2);
    int result2 = are_arrays_equal(arr1, len1, arr3, len3);
    int result3 = are_arrays_equal(arr1, len1, arr4, len4);
    int result4 = are_arrays_equal(NULL, 0, NULL, 0);
    int result5 = are_arrays_equal(arr1, len1, NULL, 0);

    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
    printf("%d\n", result4);
    printf("%d\n", result5);

    return EXIT_SUCCESS;
}