#include <stdio.h>

int multiplyList(int arr[], int n) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Product of all elements in list: %d", multiplyList(arr, n));
    return 0;
}