#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isMonotonic(int arr[], int size) {
    if (size <= 1) {
        return true;
    }

    bool isNonIncreasing = true;
    bool isNonDecreasing = true;

    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            isNonIncreasing = false;
        }
        if (arr[i] < arr[i - 1]) {
            isNonDecreasing = false;
        }
    }

    return isNonIncreasing || isNonDecreasing;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {6, 5, 4, 4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {1, 3, 2};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    if (isMonotonic(arr1, size1)) {
        printf("arr1 is monotonic.\n");
    } else {
        printf("arr1 is not monotonic.\n");
    }

    if (isMonotonic(arr2, size2)) {
        printf("arr2 is monotonic.\n");
    } else {
        printf("arr2 is not monotonic.\n");
    }

    if (isMonotonic(arr3, size3)) {
        printf("arr3 is monotonic.\n");
    } else {
        printf("arr3 is not monotonic.\n");
    }

    return 0;
}