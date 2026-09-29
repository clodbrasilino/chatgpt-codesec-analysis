#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n) {
    int positiveIndex = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            int temp = arr[i];
            for (int j = i; j > positiveIndex; j--) {
                arr[j] = arr[j - 1];
            }
            arr[positiveIndex] = temp;
            positiveIndex++;
        }
    }
}

int main() {
    int arr[] = {12, 11, -13, -5, 6, -7, 5, -3, -6};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}