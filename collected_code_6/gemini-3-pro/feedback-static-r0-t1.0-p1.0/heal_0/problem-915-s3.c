#include <stdio.h>
#include <stdlib.h>

void rearrangeArray(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (i != j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j++;
        }
    }
}

int main() {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, -9};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrangeArray(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}