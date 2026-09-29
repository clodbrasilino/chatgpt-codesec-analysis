#include <stdio.h>

int findLeftInsertionPoint(const int arr[], int n, int value) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int value = 4;
    
    int insertionPoint = findLeftInsertionPoint(arr, n, value);
    printf("Insertion Point: %d\n", insertionPoint);

    return 0;
}