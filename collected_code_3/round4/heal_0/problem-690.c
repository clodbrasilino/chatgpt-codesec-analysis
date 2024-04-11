#include <stdio.h>

int multiply_consecutive_numbers(int arr[], int n) {
    int result = 1;
    for(int i = 0; i < n; i++) {
        result *= arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = multiply_consecutive_numbers(arr, n);
    printf("The result is %d\n", result);
    return 0;
}