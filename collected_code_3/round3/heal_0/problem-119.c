#include <stdio.h>

int findSingle(int arr[], int low, int high) {
    if (low > high)
        return -1;

    if (low == high)
        return arr[low];

    int mid = (low + high) / 2;

    if (mid % 2 == 0) {
        if (arr[mid] == arr[mid + 1])
            return findSingle(arr, mid + 2, high);
        else
            return findSingle(arr, low, mid);
    } else {
        if (arr[mid] == arr[mid - 1])
            return findSingle(arr, mid + 1, high);
        else
            return findSingle(arr, low, mid - 1);
    }
}

int main() {
    int arr[] = {1, 1, 2, 4, 4, 5, 5, 6, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("The element that appears only once is %d", findSingle(arr, 0, len - 1));
    return 0;
}