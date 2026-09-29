#include <stdio.h>

int sum_negative_numbers(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] < 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = sum_negative_numbers(arr, n);
    printf("Sum of negative numbers: %d\n", sum);
    return 0;
}