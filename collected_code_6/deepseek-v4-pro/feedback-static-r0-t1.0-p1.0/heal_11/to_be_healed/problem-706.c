#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int is_subset(int arr1[], int n1, int arr2[], int n2) {
    if (arr1 == NULL || arr2 == NULL) {
        return 1;
    }
    if (n1 < 0 || n2 < 0) {
        return 1;
    }
    if (n2 == 0) {
        return 0;
    }
    if (n1 == 0) {
        return 1;
    }

    if (n1 > (int)(SIZE_MAX / sizeof(int)) || n2 > (int)(SIZE_MAX / sizeof(int))) {
        return 1;
    }

    size_t size1 = (size_t)n1 * sizeof(int);
    size_t size2 = (size_t)n2 * sizeof(int);

    int *sorted_arr1 = (int *)malloc(size1);
    int *sorted_arr2 = (int *)malloc(size2);
    if (sorted_arr1 == NULL || sorted_arr2 == NULL) {
        free(sorted_arr1);
        free(sorted_arr2);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_arr1, arr1, size1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_arr2, arr2, size2);

    qsort(sorted_arr1, (size_t)n1, sizeof(int), compare_ints);
    qsort(sorted_arr2, (size_t)n2, sizeof(int), compare_ints);

    int i = 0;
    int j = 0;
    while (i < n1 && j < n2) {
        if (sorted_arr1[i] < sorted_arr2[j]) {
            i++;
        } else if (sorted_arr1[i] > sorted_arr2[j]) {
            free(sorted_arr1);
            free(sorted_arr2);
            return 1;
        } else {
            i++;
            j++;
        }
    }

    free(sorted_arr1);
    free(sorted_arr2);

    if (j == n2) {
        return 0;
    }
    return 1;
}

int main(void) {
    int arr1[] = {5, 1, 22, 25, 6, -1, 8, 10};
    int arr2[] = {1, 6, -1, 10};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));

    if (is_subset(arr1, n1, arr2, n2) == 0) {
        printf("arr2 is a subset of arr1\n");
    } else {
        printf("arr2 is not a subset of arr1\n");
    }

    int arr3[] = {1, 2, 3};
    int arr4[] = {1, 4};
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int n4 = (int)(sizeof(arr4) / sizeof(arr4[0]));

    if (is_subset(arr3, n3, arr4, n4) == 0) {
        printf("arr4 is a subset of arr3\n");
    } else {
        printf("arr4 is not a subset of arr3\n");
    }

    int arr5[] = {1, 2, 3};
    int arr6[] = {0};
    int n5 = (int)(sizeof(arr5) / sizeof(arr5[0]));
    int n6 = 0;

    if (is_subset(arr5, n5, arr6, n6) == 0) {
        printf("arr6 is a subset of arr5\n");
    } else {
        printf("arr6 is not a subset of arr5\n");
    }

    return 0;
}