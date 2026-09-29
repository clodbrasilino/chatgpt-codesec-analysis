#include <stdio.h>
#include <stdbool.h>

bool isUnique(int num, int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == num) {
            return false;
        }
    }
    return true;
}

int productOfUnique(int arr[], int n) {
    int product = 1;
    for(int i = 0; i < n; i++) {
        if(isUnique(arr[i], arr, i)) {
            product *= arr[i];
        }
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Product of unique numbers is %d", productOfUnique(arr, n));
    return 0;
}