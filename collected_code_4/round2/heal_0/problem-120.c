#include <stdio.h>

long findMaxProduct(int arr[], int n) {
    if(n < 2) {
        printf("No pairs in array\n");
        return 0;
    }

    int firstMax = (arr[0] > arr[1]) ? arr[0] : arr[1];
    int secondMax = (arr[0] < arr[1]) ? arr[0] : arr[1];

    for(int i = 2; i < n; i++) {
        if(arr[i] > firstMax) {
            secondMax = firstMax;
            firstMax = arr[i];
        } else if(arr[i] > secondMax) {
            secondMax = arr[i];
        }
    }
    return (long)firstMax * secondMax;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    long maxProduct = findMaxProduct(arr, n);
    printf("Maximum Product is %ld", maxProduct);
    return 0;
}