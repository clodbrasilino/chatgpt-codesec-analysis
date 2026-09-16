#include <stdio.h>

int findSingle(int arr[], int n) {
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n-1] != arr[n-2]) return arr[n-1];

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] != arr[i+1] && arr[i] != arr[i-1])
            return arr[i];
    }
    return -1;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 4, 4, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findSingle(arr, n);
    printf("The single element is: %d\n", result);
    return 0;
}