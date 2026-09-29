#include<stdio.h>

int findMaxProduct(int arr[], int size){
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxProduct = arr[0]*arr[1];
    for(int i=2; i<size; i+=2){
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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