#include <stdio.h>

int multiplyConsecutiveNumbers(int arr[], int n) {
    int product = 1;
    for(int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = multiplyConsecutiveNumbers(arr, n);
    printf("The product of the consecutive numbers is: %d\n", result);
    return 0;
}