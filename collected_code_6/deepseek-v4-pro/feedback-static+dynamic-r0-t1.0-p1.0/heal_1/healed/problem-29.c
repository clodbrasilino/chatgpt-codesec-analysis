#include <stdio.h>
#include <stdlib.h>

int findOddOccurrence(const int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 2, 3, 1, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findOddOccurrence(arr1, size1));

    int arr2[] = {5, 7, 2, 7, 5, 2, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findOddOccurrence(arr2, size2));

    int arr3[] = {4};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", findOddOccurrence(arr3, size3));

    int arr4[] = {-2, -2, 9};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", findOddOccurrence(arr4, size4));

    return 0;
}