#include<stdio.h>

int findMaxProduct(int arr[], int size){
    int maxProduct = arr[0]*arr[1];
    for(int i=2; i<size; i+=2){
        int product = arr[i]*arr[i+1];
        if(product > maxProduct){
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int maxProduct = findMaxProduct(arr, size);
    printf("Maximum product: %d", maxProduct);
    return 0;
}