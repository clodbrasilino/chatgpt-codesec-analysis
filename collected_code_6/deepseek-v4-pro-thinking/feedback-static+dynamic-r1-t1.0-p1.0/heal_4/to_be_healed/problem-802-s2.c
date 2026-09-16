#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0, high = n - 1;

    while (low < high) {
        if (arr[low] < arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            if (arr[low] == arr[mid]) {
                low++;
                high--;
            } else {
                high--;
            }
        }
    }

    return low;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int rotations = countRotations(arr, n);

    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}