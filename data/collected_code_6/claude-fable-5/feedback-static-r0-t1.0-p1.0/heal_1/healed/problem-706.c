#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

bool is_subset(const int *arr1, size_t n1, const int *arr2, size_t n2)
{
    int *sorted;
    size_t i;
    size_t alloc_size;
    bool result = true;

    if (n2 == 0) {
        return true;
    }
    if (arr1 == NULL || arr2 == NULL || n2 > n1) {
        return false;
    }
    if (n1 > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    alloc_size = n1 * sizeof(*sorted);

    sorted = malloc(alloc_size);
    if (sorted == NULL) {
        return false;
    }

    memcpy(sorted, arr1, alloc_size);
    qsort(sorted, n1, sizeof(*sorted), compare_ints);

    for (i = 0; i < n2; i++) {
        if (bsearch(&arr2[i], sorted, n1, sizeof(*sorted), compare_ints) == NULL) {
            result = false;
            break;
        }
    }

    free(sorted);
    return result;
}

int main(void)
{
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    int arr3[] = {11, 3, 7, 1, 99};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    if (is_subset(arr1, n1, arr2, n2)) {
        if (printf("arr2 is a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr2 is not a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (is_subset(arr1, n1, arr3, n3)) {
        if (printf("arr3 is a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr3 is not a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}