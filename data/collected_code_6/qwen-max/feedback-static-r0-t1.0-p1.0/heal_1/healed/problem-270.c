#include <stdio.h>

int sumEvenAtEvenPositions(const int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sumEvenAtEvenPositions(arr, n);
    printf("Sum of even numbers at even positions: %d\n", result);
    return 0;
}