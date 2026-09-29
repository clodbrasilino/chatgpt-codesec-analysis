#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 2 failed: expected 3, got 2
  */

int countRotations(int arr[], int n) {
    if (n == 0) return 0;
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    if (min_index > 0 && arr[min_index - 1] > arr[min_index]) {
        return (min_index + 1);
    }
    return 0;
}

int main() {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = countRotations(arr, n);
    printf("Number of rotations: %d\n", rotations);
    return 0;
}