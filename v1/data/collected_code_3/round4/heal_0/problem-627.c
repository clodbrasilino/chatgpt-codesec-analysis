#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(int arr[], int n) {
    int i, total;
    total = (n + 1) * (n + 2) / 2;
    for (i = 0; i < n; i++)
        total -= arr[i];
    return total;
}

int main() {
    int arr[] = {1, 2, 4, 6, 3, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int missing = findMissingNumber(arr, n);
    printf("The smallest missing number is %d", missing);
    return 0;
}