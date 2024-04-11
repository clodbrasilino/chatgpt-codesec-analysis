#include <stdio.h>

int countPairs(int arr[], int n) {
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
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Count of pairs with even XOR is %d\n", countPairs(arr, n));
    return 0;
}