#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--; 
        }
    }

    return low;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    int rotations = count_rotations(arr, n);
    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        free(arr);
        return 1;
    }

    free(arr);
    return 0;
}