#include <stdio.h>
#include <stdlib.h>

int isSubset(const int *arr1, int size1, const int *arr2, int size2) {
    if (arr1 == NULL || arr2 == NULL) {
        return -1;
    }

    if (size2 == 0) {
        return 1;
    }

    if (size1 == 0) {
        return 0;
    }

    int *count = (int *)calloc(1001, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    for (int i = 0; i < size1; i++) {
        if (arr1[i] >= 0 && arr1[i] <= 1000) {
            count[arr1[i]]++;
        }
    }

    for (int i = 0; i < size2; i++) {
        if (arr2[i] < 0 || arr2[i] > 1000) {
            free(count);
            return 0;
        }
        if (count[arr2[i]] == 0) {
            free(count);
            return 0;
        }
        count[arr2[i]]--;
    }

    free(count);
    return 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {2, 4, 6};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {2, 4, 9};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    int result1 = isSubset(arr1, size1, arr2, size2);
    int result2 = isSubset(arr1, size1, arr3, size3);

    if (result1 == 1) {
        printf("True\n");
    } else if (result1 == 0) {
        printf("False\n");
    } else {
        printf("Memory allocation failed for arr2 check\n");
    }

    if (result2 == 1) {
        printf("True\n");
    } else if (result2 == 0) {
        printf("False\n");
    } else {
        printf("Memory allocation failed for arr3 check\n");
    }

    return 0;
}