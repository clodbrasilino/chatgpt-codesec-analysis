#include <stdio.h>
#include <stdlib.h>

int productOfUnique(int* arr, int n) {
    int product = 1;
    for(int i = 0; i < n; i++) {
        int j;
        for(j = 0; j < i; j++)
           if(arr[i] == arr[j])
               break;
        if(i == j)
            product *= arr[i];
    }
    return product;
}

int main() {
    int arr[] = {10, 20, 30, 20, 40, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", productOfUnique(arr, n));
    return 0;
}