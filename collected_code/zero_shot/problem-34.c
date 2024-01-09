#include <stdio.h>

int findMissingNumber(int arr[], int size) {
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (arr[mid] != mid + 1 && arr[mid - 1] == mid) {
            return mid + 1;
        }
        else if (arr[mid] != mid + 1) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1; // No missing number found
}

int main() {
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    int missingNumber = findMissingNumber(arr, size);

    printf("The missing number is: %d\n", missingNumber);

    return 0;
}