#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 1
  *  test case 1 failed: expected 2, got 1
  */

int count_rotations(const int *arr, int n) {
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    const int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = count_rotations(arr, n);
    printf("Number of rotations: %d\n", rotations);
    return 0;
}