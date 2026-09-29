#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findRotations(int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    if (arr[low] <= arr[high]) {
        return 0;
    }

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else if (arr[mid] >= arr[low]) {
            low = mid + 1;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    int rotations = findRotations(arr, n);

    if (rotations != -1) {
        printf("The array is rotated %d times.\n", rotations);
    } else {
        printf("Invalid input or unrotated array.\n");
    }

    return 0;
}