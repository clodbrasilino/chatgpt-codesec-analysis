#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_one_distinct_element(const int *array, size_t size) {
    if (size == 0) {
        return false;
    }

    int first = array[0];

    for (size_t i = 1; i < size; i++) {
        if (array[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5};
    int arr2[] = {5, 5, 2, 5};
    int arr3[] = {10};
    int const * arr4 = NULL;
    size_t size4 = 0;

    printf("arr1: %d\n", has_one_distinct_element(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("arr2: %d\n", has_one_distinct_element(arr2, sizeof(arr2) / sizeof(arr2[0])));
    printf("arr3: %d\n", has_one_distinct_element(arr3, sizeof(arr3) / sizeof(arr3[0])));
    printf("arr4: %d\n", has_one_distinct_element(arr4, size4));

    return 0;
}