#include <stdio.h>

long long int product_of_tuple(int arr[], int n) {
    long long int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Product of all numbers in tuple is %lld\n", product_of_tuple(arr, n));
    return 0;
}