#include <stdio.h>

void shiftLastToFirst(int arr[], int n) {
    int temp = arr[n-1], i;
    for (i = n-1; i > 0; i--)
        arr[i] = arr[i-1];
    arr[0] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}, i;
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Original array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    shiftLastToFirst(arr, n);

    printf("\nModified array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}