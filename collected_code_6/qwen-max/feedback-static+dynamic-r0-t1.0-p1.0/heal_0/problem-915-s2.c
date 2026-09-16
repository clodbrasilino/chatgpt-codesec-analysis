#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int n) {
    int temp[n], i, j;
    for (i = 0, j = n-1; i < j; ) {
        while (i < n && arr[i] < 0) i++;
        while (j >= 0 && arr[j] > 0) j--;
        if (i < j) {
            temp[i] = arr[j];
            temp[j] = arr[i];
            i++; j--;
        }
    }
    for (int k = 0; k < n; k++) {
        arr[k] = temp[k];
    }
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}