#include <stdio.h>

int findProduct(int arr[], int n) {
    int firstEven = -1, firstOdd = -1;
    for (int i = 0; i < n; i++) {
        if (firstEven == -1 && arr[i] % 2 == 0) {
            firstEven = arr[i];
        }
        if (firstOdd == -1 && arr[i] % 2 != 0) {
            firstOdd = arr[i];
        }
        if (firstEven != -1 && firstOdd != -1) {
            break;
        }
    }
    return firstEven * firstOdd;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", findProduct(arr, n));
    return 0;
}