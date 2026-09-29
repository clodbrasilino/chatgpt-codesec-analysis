#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_one_distinct_element(const int *array, size_t size) {
    if (array == NULL) {
        return false;
    }

    if (size == 0) {
        return false;
    }

    int first_element = array[0];

    for (size_t i = 1; i < size; i++) {
        if (array[i] != first_element) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {1, 2, 3, 4};
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {42};
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    const int * const arr4 = NULL;
    size_t len4 = 0;

    bool res1 = has_one_distinct_element(arr1, len1);
    bool res2 = has_one_distinct_element(arr2, len2);
    bool res3 = has_one_distinct_element(arr3, len3);
    bool res4 = has_one_distinct_element(arr4, len4);

    printf("Array 1 result: %d\n", res1);
    printf("Array 2 result: %d\n", res2);
    printf("Array 3 result: %d\n", res3);
    printf("Array 4 result: %d\n", res4);

    return 0;
}