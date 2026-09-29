#include <stdio.h>

int getEvenXORPairCount(int arr[], int n) {
    int even_count = 0, odd_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            even_count++;
        else
            odd_count++;
    }
    return (even_count * (even_count - 1) / 2) + (odd_count * (odd_count - 1) / 2);
}

int main() {
    int arr[] = {3, 2, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = getEvenXORPairCount(arr, n);
    printf("%d", count);
    return 0;
}