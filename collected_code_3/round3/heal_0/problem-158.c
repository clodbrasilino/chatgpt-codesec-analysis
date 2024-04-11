#include <stdio.h>
#include <stdlib.h>

int findOperations(int arr[], int n, int k) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int operations = 0;
    for (int i = 0; i < n; i++) {
        operations += (max - arr[i]) / k;
        if ((max - arr[i]) % k != 0) {
            operations++;
        }
    }

    return operations;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    printf("Number of operations required to make all elements equal is %d\n", findOperations(arr, n, k));
    return 0;
}