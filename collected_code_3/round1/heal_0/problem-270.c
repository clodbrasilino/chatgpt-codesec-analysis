#include <stdio.h>

int sumEvenNumbersAtEvenPositions(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0 && arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = sumEvenNumbersAtEvenPositions(arr, n);
    printf("Sum of even numbers at even positions: %d\n", sum);
    return 0;
}