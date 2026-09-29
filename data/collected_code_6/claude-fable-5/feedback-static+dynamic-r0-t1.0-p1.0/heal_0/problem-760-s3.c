#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_single_distinct_element(const int *arr, size_t len)
{
    size_t i;

    if (arr == NULL || len == 0U) {
        return false;
    }

    for (i = 1U; i < len; i++) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int arr1[] = {5, 5, 5, 5, 5};
    int arr2[] = {1, 2, 1, 1, 1};
    int arr3[] = {7};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    if (has_single_distinct_element(arr1, len1)) {
        (void)printf("arr1 contains only one distinct element\n");
    } else {
        (void)printf("arr1 contains more than one distinct element\n");
    }

    if (has_single_distinct_element(arr2, len2)) {
        (void)printf("arr2 contains only one distinct element\n");
    } else {
        (void)printf("arr2 contains more than one distinct element\n");
    }

    if (has_single_distinct_element(arr3, len3)) {
        (void)printf("arr3 contains only one distinct element\n");
    } else {
        (void)printf("arr3 contains more than one distinct element\n");
    }

    return EXIT_SUCCESS;
}