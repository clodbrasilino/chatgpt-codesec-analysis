#include <stdio.h>

int find_largest_product(int arr[], int n) {
    if(n < 2) {
        printf("Not enough elements in the array");
        return 0;
    }

    int max_product = arr[0] * arr[1];  
    for (int i=1; i<n-1; i++) {
        if (arr[i]*arr[i+1] > max_product)
            max_product = arr[i] * arr[i+1];
    }
    return max_product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr)/sizeof(arr[0]);
    int max_prod = find_largest_product(arr, size);
    printf("Maximum product is %d\n", max_prod);
    return 0;
}