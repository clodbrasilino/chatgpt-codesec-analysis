#include <stdio.h>
#include <stdlib.h>

int count_rotations(const int *arr, int n) {
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    while (min_index > 0 && arr[min_index - 1] == arr[min_index]) {
        min_index--;
    }
    return min_index;
}

int find_pivot(const int *arr, int n) {
    int low = 0, high = n - 1;
    while (low < high) {
        if (arr[low] < arr[high]) {
            high--;
        } else {
            low++;
        }
    }
    return low;
}

int main() {
    const int arr1[] = {2, 3, 6, 12, 15, 18};
    const int arr2[] = {6, 12, 15, 18, 2, 3};
    const int arr3[] = {15, 18, 2, 3, 6, 12};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    int rotations1 = find_pivot(arr1, n1);
    int rotations2 = find_pivot(arr2, n2);
    int rotations3 = find_pivot(arr3, n3);

    printf("Number of rotations in arr1: %d\n", rotations1);
    printf("Number of rotations in arr2: %d\n", rotations2);
    printf("Number of rotations in arr3: %d\n", rotations3);

    return 0;
}