#include <stdio.h>

int countPairs(int arr[], int n) {
    int odd = 0, even = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            even++;
        else
            odd++;
    }
    return odd * (odd - 1) / 2 + even * (even - 1) / 2;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", countPairs(arr, n));
    return 0;
}