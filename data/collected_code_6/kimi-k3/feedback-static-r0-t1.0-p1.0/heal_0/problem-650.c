#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool areArraysEqual(const int arr1[], const int arr2[], size_t size1, size_t size2)
{
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (size1 != size2) {
        return false;
    }

    for (size_t i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {1, 2, 3, 4, 5};
    int array3[] = {1, 2, 3, 4, 6};

    size_t size1 = sizeof(array1) / sizeof(array1[0]);
    size_t size2 = sizeof(array2) / sizeof(array2[0]);
    size_t size3 = sizeof(array3) / sizeof(array3[0]);

    if (areArraysEqual(array1, array2, size1, size2)) {
        printf("array1 and array2 are equal.\n");
    } else {
        printf("array1 and array2 are not equal.\n");
    }

    if (areArraysEqual(array1, array3, size1, size3)) {
        printf("array1 and array3 are equal.\n");
    } else {
        printf("array1 and array3 are not equal.\n");
    }

    return 0;
}