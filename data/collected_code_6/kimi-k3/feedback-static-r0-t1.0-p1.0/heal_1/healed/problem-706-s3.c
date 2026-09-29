#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool is_subset(const int *arr1, size_t size1, const int *arr2, size_t size2)
{
    size_t i;
    size_t j;

    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (size1 == 0) {
        return true;
    }

    if (size2 == 0 || size1 > size2) {
        return false;
    }

    for (i = 0; i < size1; i++) {
        bool found = false;
        for (j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int arr1[] = {1, 3, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    if (is_subset(arr1, size1, arr2, size2)) {
        printf("arr1 is a subset of arr2\n");
    } else {
        printf("arr1 is not a subset of arr2\n");
    }

    if (is_subset(arr3, size3, arr2, size2)) {
        printf("arr3 is a subset of arr2\n");
    } else {
        printf("arr3 is not a subset of arr2\n");
    }

    return 0;
}