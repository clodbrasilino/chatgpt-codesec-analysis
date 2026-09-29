#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

bool contains_duplicate(const int *nums, size_t nums_size) {
    if (nums == NULL || nums_size < 2) {
        return false;
    }

    int *sorted = malloc(nums_size * sizeof(int));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0; i < nums_size; i++) {
        sorted[i] = nums[i];
    }

    qsort(sorted, nums_size, sizeof(int), cmp);

    bool result = false;
    for (size_t i = 1; i < nums_size; i++) {
        if (sorted[i] == sorted[i - 1]) {
            result = true;
            break;
        }
    }

    free(sorted);

    return result;
}

int main(void) {
    const int arr1[] = {1, 2, 3, 4, 5};
    const int arr2[] = {1, 2, 3, 2, 5};
    const int arr3[] = {7};
    const int *arr4 = NULL;

    if (contains_duplicate(arr1, sizeof(arr1) / sizeof(arr1[0]))) {
        printf("arr1 contains duplicates\n");
    } else {
        printf("arr1 does not contain duplicates\n");
    }

    if (contains_duplicate(arr2, sizeof(arr2) / sizeof(arr2[0]))) {
        printf("arr2 contains duplicates\n");
    } else {
        printf("arr2 does not contain duplicates\n");
    }

    if (contains_duplicate(arr3, 1)) {
        printf("arr3 contains duplicates\n");
    } else {
        printf("arr3 does not contain duplicates\n");
    }

    if (contains_duplicate(arr4, 0) != false) {
        printf("arr4 contains duplicates\n");
    } else {
        printf("arr4 does not contain duplicates\n");
    }

    return 0;
}