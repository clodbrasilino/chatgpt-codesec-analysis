#include <stdio.h>

int sumAlternateChains(int arr[][2], int n) {
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < 2; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}

int main() {
    int arr[][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = sumAlternateChains(arr, n);
    printf("Sum of alternate chains of tuples is %d\n", sum);
    return 0;
}