#include <stdio.h>
#include <stdbool.h>

bool areArraysEqual(int arr1[], int arr2[], int size1, int size2) {
    if (size1 != size2) {
        return false;
    }
    for (int i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (areArraysEqual(arr1, arr2, size1, size2)) {
        printf("Arrays are equal.\n");
    } else {
        printf("Arrays are not equal.\n");
    }

    return 0;
}