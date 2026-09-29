#include <stdio.h>

void swapValues(int *arr, int n) {
    for(int i = 0; i < n-1; i += 2) {
        int temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);

    swapValues(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}