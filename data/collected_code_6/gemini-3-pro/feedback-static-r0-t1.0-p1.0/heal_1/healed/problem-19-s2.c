#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool contains_duplicate(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }

    int *arr_copy = (int *)malloc(size * sizeof(int));
    if (arr_copy == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        arr_copy[i] = arr[i];
    }

    qsort(arr_copy, size, sizeof(int), compare_ints);

    bool has_duplicate = false;
    for (size_t i = 1; i < size; ++i) {
        if (arr_copy[i] == arr_copy[i - 1]) {
            has_duplicate = true;
            break;
        }
    }

    free(arr_copy);
    return has_duplicate;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 2, 3, 4, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    bool res1 = contains_duplicate(arr1, size1);
    bool res2 = contains_duplicate(arr2, size2);

    if (res1) {
        printf("arr1 contains duplicates\n");
    } else {
        printf("arr1 does not contain duplicates\n");
    }

    if (res2) {
        printf("arr2 contains duplicates\n");
    } else {
        printf("arr2 does not contain duplicates\n");
    }

    return 0;
}