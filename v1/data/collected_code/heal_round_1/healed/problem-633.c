#include <stdio.h>

int findSumOfXorPairs(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {       
            sum += arr[i] ^ arr[j];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = findSumOfXorPairs(arr, n);
    printf("Sum of XOR of all pairs: %d\n", sum);
    return 0;
}