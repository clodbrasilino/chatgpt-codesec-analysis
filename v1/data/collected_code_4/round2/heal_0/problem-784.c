#include <stdio.h>

int productEvenOdd(int arr[], int n) {
    int even = -1;
    int odd = -1;
    int product;
    for(int i = 0; i < n; i++) {
        if(odd == -1 && arr[i] % 2 != 0){
            odd = arr[i];
        }
        if(even == -1 && arr[i] % 2 == 0){
            even = arr[i];
        }
        if(odd != -1 && even != -1){
            break;
        }
    }
    if(even == -1 || odd == -1){
        return -1;
    }
    product = odd*even;
    return product;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = productEvenOdd(arr, n);
    if(result == -1){
        printf("There is no even or odd element in the list");
    }else{
        printf("Product of first even and odd number is %d", result);
    }
    return 0;
}