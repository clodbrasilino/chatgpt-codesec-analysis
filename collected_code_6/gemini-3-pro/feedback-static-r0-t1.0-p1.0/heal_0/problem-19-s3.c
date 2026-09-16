#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);

    if (int_a == int_b) {
        return 0;
    } else if (int_a < int_b) {
        return -1;
    } else {
        return 1;
    }
}

bool contains_duplicate(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return false;
    }

    qsort(array, size, sizeof(int), compare_ints);

    for (size_t i = 1; i < size; i++) {
        if (array[i] == array[i - 1]) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    if (contains_duplicate(arr1, size1)) {
        printf("Array 1 contains duplicates.\n");
    } else {
        printf("Array 1 does not contain duplicates.\n");
    }

    int arr2[] = {1, 2, 3, 4, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (contains_duplicate(arr2, size2)) {
        printf("Array 2 contains duplicates.\n");
    } else {
        printf("Array 2 does not contain duplicates.\n");
    }

    return EXIT_SUCCESS;
}