#include <stdio.h>

int countRotations(const int arr[], int n) {
    int low;
    int high;
    int mid;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = low + (high - low) / 2;

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