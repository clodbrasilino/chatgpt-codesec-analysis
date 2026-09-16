#include <stdio.h>
#include <stdbool.h>

bool isMonotonic(const int arr[], int size) {
    if (size <= 2) {
        return true;
    }

    bool isIncreasing = true;
    bool isDecreasing = true;

    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            isDecreasing = false;
        }
        if (arr[i] < arr[i - 1]) {
            isIncreasing = false;
        }
    }

    return isIncreasing || isDecreasing;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", isMonotonic(arr1, size1));

    int arr2[] = {6, 5, 4, 4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", isMonotonic(arr2, size2));

    int arr3[] = {1, 3, 2};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", isMonotonic(arr3, size3));

    return 0;
}