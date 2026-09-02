#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(const int *arr, int n) {
    int total = (n + 1) * (n + 2) / 2;
    for (int i = 0; i < n; i++) {
        total -= arr[i];
    }
    return total;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int missing = findMissingNumber(arr, n);
    printf("The missing number is %d\n", missing);
    return 0;
}