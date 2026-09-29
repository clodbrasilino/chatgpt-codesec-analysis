#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n) {
    int temp[n];
    int j = 0, k = n - 1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            temp[j++] = arr[i];
        } else {
            temp[k--] = arr[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = temp[i];
    }
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}