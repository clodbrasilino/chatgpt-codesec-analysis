#include <stdio.h>

int findLastOccurrence(int arr[], int n, int x) {
    int start = 0, end = n - 1;
    int result = -1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (x == arr[mid]) {
            result = mid;
            start = mid + 1;
        }
        else if (x < arr[mid]) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4, 7, 8, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 2;
    int index = findLastOccurrence(arr, n, x);
    if (index != -1) {
        printf("Last occurrence of %d is at index %d\n", x, index);
    }
    else {
        printf("%d is not present in array\n", x);
    }
    return 0;
}