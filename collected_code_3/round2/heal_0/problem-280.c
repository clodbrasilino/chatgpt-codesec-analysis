#include <stdio.h>

int sequentialSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 110;
    int result = sequentialSearch(arr, n, x);
    if(result != -1) {
        printf("Element is present at index %d", result);
    } else {
        printf("Element is not present in array");
    }
    return 0;
}