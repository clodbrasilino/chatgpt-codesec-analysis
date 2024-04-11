#include <stdio.h>

long long int sumOfProduct(int arr[], int n) {
    long long int sum = 0;
    for (int i = 0; i < n; i++) {
        long long int product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            sum += product;
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", sumOfProduct(arr, n));
    return 0;
}