#include <stdio.h>

void rearrangeArray(int arr[], int n) {
    int positiveIndex = 0;
    int negativeIndex = 1;

    while (positiveIndex < n && negativeIndex < n) {
        while (positiveIndex < n && arr[positiveIndex] >= 0) {
            positiveIndex += 2;
        }

        while (negativeIndex < n && arr[negativeIndex] <= 0) {
            negativeIndex += 2;
        }

        if (positiveIndex < n && negativeIndex < n) {
            int temp = arr[positiveIndex];
            arr[positiveIndex] = arr[negativeIndex];
            arr[negativeIndex] = temp;
        }
    }
}

int main() {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    rearrangeArray(arr, n);

    printf("\nRearranged array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}