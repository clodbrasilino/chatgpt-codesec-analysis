#include <stdio.h>

int largestProduct(int arr[], int size) {
    int largestProd = arr[0] * arr[1];
    
    for (int i = 1; i < size - 1; i++) {
        int product = arr[i] * arr[i + 1];
        if (product > largestProd) {
            largestProd = product;
        }
    }
    
    return largestProd;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = largestProduct(arr, size);
    printf("Largest product of adjacent elements: %d\n", result);
    
    return 0;
}