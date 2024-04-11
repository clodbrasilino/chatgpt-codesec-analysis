#include <stdio.h>

void printPositiveNumbers(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] > 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {-1, 2, -3, 4, -5, 6, -7, 8, -9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printPositiveNumbers(arr, n);

    return 0;
}