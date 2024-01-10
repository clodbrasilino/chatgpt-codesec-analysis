#include <stdio.h>

int maxProduct(const int arr[], int n) {
    int result = -1;
    int product = 1;

    for (int i = 0; i < n-1; i++) {
        if (arr[i] < arr[i+1]) {
            product *= arr[i];
        } else {
            product *= arr[i];
            if (product > result) {
                result = product;
            }
            product = 1;
        }
    }

    if(product > result){
        result = product;
    }
    
    return result;
}

int main() {
    int arr[] = {3, 2, 5, 4, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum product: %d\n", maxProduct(arr, n));

    return 0;
}