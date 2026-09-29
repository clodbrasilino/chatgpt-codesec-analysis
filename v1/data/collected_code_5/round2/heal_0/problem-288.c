#include<stdio.h>

int countSelfInverses(int arr[], int n, int p) {
    int count = 0;
    int rem = 0;
    
    for (int i = 0; i < n; i++) {
        rem = arr[i] % p;
        if (rem * rem % p == 1 && rem == arr[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 7;
    
    int count = countSelfInverses(arr, n, p);
    printf("Count of numbers having modular inverse equal to themselves: %d", count);
    
    return 0;
}