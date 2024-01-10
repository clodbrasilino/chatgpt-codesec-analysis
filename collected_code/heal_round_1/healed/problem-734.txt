#include<stdio.h>

int sum_of_products(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            sum += product;
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sum_of_products(arr, n);
    printf("Sum of products of all possible subarrays is %d\n", result);
    return 0;
}