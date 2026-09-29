#include <stdio.h>

int sum_even_at_even(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    const int arr[] = {1, 3, 6, 8, 10, 15, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sum_even_at_even(arr, n);
    printf("Sum of even numbers at even positions: %d\n", result);
    return 0;
}