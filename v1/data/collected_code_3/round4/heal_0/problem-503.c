#include <stdio.h>

int add_consecutive_numbers(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = add_consecutive_numbers(arr, n);
    printf("Sum of consecutive numbers: %d\n", sum);
    return 0;
}