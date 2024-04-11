#include <stdio.h>

void swapFirstAndLast(int arr[], int n) {
    int temp = arr[0];
    arr[0] = arr[n-1];
    arr[n-1] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    swapFirstAndLast(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}