#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 3, got 1
  */

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
        int mid = low + (high - low) / 2;
        if (arr[mid] <= arr[high]) {
            high = mid;
        } else {
            low = mid + 1;
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

    int rotations1 = count_rotations(arr1, n1);
    int rotations2 = count_rotations(arr2, n2);
    int rotations3 = count_rotations(arr3, n3);

    printf("Number of rotations in arr1: %d\n", rotations1);
    printf("Number of rotations in arr2: %d\n", rotations2);
    printf("Number of rotations in arr3: %d\n", rotations3);

    return 0;
}