#include <stdio.h>
#include <stdbool.h>

bool has_one_distinct_element(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return false;
    }

    int first_element = array[0];

    for (size_t i = 1; i < size; ++i) {
        if (array[i] != first_element) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    if (has_one_distinct_element(arr1, size1)) {
        printf("arr1 contains only one distinct element.\n");
    } else {
        printf("arr1 does not contain only one distinct element.\n");
    }

    int arr2[] = {5, 5, 4, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (has_one_distinct_element(arr2, size2)) {
        printf("arr2 contains only one distinct element.\n");
    } else {
        printf("arr2 does not contain only one distinct element.\n");
    }

    return 0;
}