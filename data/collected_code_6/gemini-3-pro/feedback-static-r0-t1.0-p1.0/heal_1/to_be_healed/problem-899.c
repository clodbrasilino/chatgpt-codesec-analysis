#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canBeSorted(const int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return false;
    }
    if (n == 1) {
        return true;
    }

    bool isSorted = true;
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            isSorted = false;
            break;
        }
    }
    if (isSorted) {
        return true;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'arr[0]<=arr[n-1]' is not redundant
     */
    if (arr[0] <= arr[n - 1]) {
        return false;
    }

    size_t splitPoint = 0;
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            if (splitPoint != 0) {
                return false;
            }
            splitPoint = i;
        }
    }

    /* Possible weaknesses found:
     *  Return value 'arr[n-1]<=arr[0]' is always true [knownConditionTrueFalse]
     *  Return value 'arr[n-1]<=arr[0]' is always true
     */
    return arr[n - 1] <= arr[0];
}

int main() {
    int arr1[] = {3, 4, 5, 1, 2};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    if (canBeSorted(arr1, n1)) {
        printf("Array 1 can be sorted.\n");
    } else {
        printf("Array 1 cannot be sorted.\n");
    }

    int arr2[] = {3, 4, 1, 5, 2};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    if (canBeSorted(arr2, n2)) {
        printf("Array 2 can be sorted.\n");
    } else {
        printf("Array 2 cannot be sorted.\n");
    }

    return 0;
}