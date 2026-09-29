#include <stdio.h>
#include <stdlib.h>

int count_rotations(const int *arr, int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            break;
        }
    }
    return (i + 1) % n;
}

int main() {
    const int arr1[] = {2, 3, 6, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", count_rotations(arr1, n1));

    const int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", count_rotations(arr2, n2));

    const int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", count_rotations(arr3, n3));

    return 0;
}