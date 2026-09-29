#include <stdio.h>
#include <stddef.h>

int has_only_one_distinct_element(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int first = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5};
    int arr2[] = {5, 5, 6, 5};
    int arr3[] = {42};
    int arr4[] = {1, 2, 3, 4};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("arr1: %s\n", has_only_one_distinct_element(arr1, size1) ? "yes" : "no");
    printf("arr2: %s\n", has_only_one_distinct_element(arr2, size2) ? "yes" : "no");
    printf("arr3: %s\n", has_only_one_distinct_element(arr3, size3) ? "yes" : "no");
    printf("arr4: %s\n", has_only_one_distinct_element(arr4, size4) ? "yes" : "no");

    return 0;
}