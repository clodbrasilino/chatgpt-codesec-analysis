#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_one_distinct_element(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }

    int first = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const int arr1[] = {5, 5, 5, 5};
    const int arr2[] = {1, 2, 3, 4};
    const int arr3[] = {0};
    const int arr4[] = {7};
    size_t arr4_size = 1;

    bool res1 = has_one_distinct_element(arr1, 4);
    bool res2 = has_one_distinct_element(arr2, 4);
    bool res3 = has_one_distinct_element(arr3, 1);
    bool res4 = has_one_distinct_element(arr4, arr4_size);

    printf("arr1: %s\n", res1 ? "true" : "false");
    printf("arr2: %s\n", res2 ? "true" : "false");
    printf("arr3: %s\n", res3 ? "true" : "false");
    printf("arr4: %s\n", res4 ? "true" : "false");

    return 0;
}