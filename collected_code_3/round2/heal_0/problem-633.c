#include <stdio.h>

int sumXOR(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += arr[i] ^ arr[j];
        }
    }
    return sum;
}

int main() {
    int arr[] = {5, 9, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Sum of XOR of all pairs is %d", sumXOR(arr, n));
    return 0;
}