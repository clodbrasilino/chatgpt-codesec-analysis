#include <stdio.h>
#include <stdbool.h>

bool isSubArray(int *arr1, int size1, int *arr2, int size2) {
    int i = 0, j = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] == arr2[j]) {
            i++;
            j++;
            if (j == size2) {
                return true;
            }
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    return false;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[] = {3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    if (isSubArray(arr1, size1, arr2, size2)) {
        printf("Array2 is a subarray of Array1\n");
    } else {
        printf("Array2 is not a subarray of Array1\n");
    }

    return 0;
}