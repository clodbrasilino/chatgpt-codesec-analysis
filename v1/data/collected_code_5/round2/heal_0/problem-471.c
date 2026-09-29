#include <stdio.h>

long long findRemainder(int arr[], int size, int n) {
    long long mul = 1;

    for (int i = 0; i < size; i++) {
        if(arr[i] == 0) return 0;
        mul *= (arr[i] % n);
    }

    return mul % n;
}

int main() {
    int arr[] = {100, 10, 5, 25, 35, 14}; 
    int n = 11; 

    int size = sizeof(arr)/sizeof(arr[0]);
    printf("%lld", findRemainder(arr,size,n));

    return 0; 
}