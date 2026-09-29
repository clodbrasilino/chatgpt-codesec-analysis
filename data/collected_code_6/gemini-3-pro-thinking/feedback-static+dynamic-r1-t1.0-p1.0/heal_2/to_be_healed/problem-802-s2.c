#include <stdio.h>
#include <stdlib.h>

int count_rotations(const int *arr, int n);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        
        int next = (mid == n - 1) ? 0 : (mid + 1);
        int prev = (mid == 0) ? (n - 1) : (mid - 1);

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[low] <= arr[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    int capacity = 100000;
    int *arr = (int *)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    int n = 0;
    while (scanf("%d", &arr[n]) == 1) {
        n++;
        if (n >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                free(arr);
                return 1;
            }
            arr = temp;
        }
    }

    if (n > 0) {
        int rotations = count_rotations(arr, n);
        if (rotations >= 0) {
            printf("%d\n", rotations);
        } else {
            free(arr);
            return 1;
        }
    }

    free(arr);
    return 0;
}