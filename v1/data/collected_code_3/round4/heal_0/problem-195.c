#include <stdio.h>

int findFirstPosition(int arr[], int n, int x) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (x > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (low < n && arr[low] == x)
        return low;

    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 5;
    int result = findFirstPosition(arr, n, x);

    if (result != -1)
        printf("Element %d found at index %d\n", x, result);
    else
        printf("Element %d not found in the array\n", x);

    return 0;
}