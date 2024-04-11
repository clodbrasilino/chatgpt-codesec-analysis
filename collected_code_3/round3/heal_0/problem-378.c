#include <stdio.h>

void shiftLastToFirst(int arr[], int n) {
    int i, last;
    last = arr[n - 1];

    for (i = n - 2; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }

    arr[0] = last;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    shiftLastToFirst(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}