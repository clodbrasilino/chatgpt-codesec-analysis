#include <stdio.h>

int findFirstOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (x == arr[mid]) {
            result = mid;
            high = mid - 1;
        }
        else if (x < arr[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 2;
    int index = findFirstOccurrence(arr, n, x);
    if (index != -1)
        printf("First occurrence of %d is at index %d", x, index);
    else
        printf("%d is not in the array", x);
    return 0;
}