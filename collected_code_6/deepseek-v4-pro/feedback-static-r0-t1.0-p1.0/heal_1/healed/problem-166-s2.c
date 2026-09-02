#include <stdio.h>

int countPairsWithEvenXor(const int arr[], int n) {
    int even = 0, odd = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) even++;
        else odd++;
    }
    return (even * (even - 1) / 2) + (odd * (odd - 1) / 2);
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countPairsWithEvenXor(arr, n);
    printf("%d\n", result);
    return 0;
}