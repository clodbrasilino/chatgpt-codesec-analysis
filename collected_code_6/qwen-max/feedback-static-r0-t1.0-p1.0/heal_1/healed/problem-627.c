#include <stdio.h>
#include <stdbool.h>

int findSmallestMissing(const int arr[], int n) {
    bool present[n+1];
    for (int i = 0; i <= n; i++) {
        present[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] <= n) {
            present[arr[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!present[i]) {
            return i;
        }
    }
    return n + 1;
}

int main() {
    const int arr[] = {3, 4, -1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The smallest missing number is %d\n", findSmallestMissing(arr, n));
    return 0;
}