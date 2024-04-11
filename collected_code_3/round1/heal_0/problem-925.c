#include <stdio.h>

int productOfTuple(int arr[], int n) {
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Product of all numbers in the tuple is %d", productOfTuple(arr, n));
    return 0;
}