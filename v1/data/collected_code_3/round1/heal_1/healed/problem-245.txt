#include <stdio.h>
#include <stdlib.h>

int bitonic(int arr[], int n) {
    int *inc = (int *) malloc(sizeof(int) * n);
    int *dec = (int *) malloc(sizeof(int) * n);
    int max;

    if (inc == NULL || dec == NULL)
        return -1;

    inc[0] = 1;
    dec[n - 1] = 1;

    for (int i = 1; i < n; i++) {
        inc[i] = (arr[i] >= arr[i - 1]) ? inc[i - 1] + 1 : 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        dec[i] = (arr[i] >= arr[i + 1]) ? dec[i + 1] + 1 : 1;
    }

    max = inc[0] + dec[0] - 1;
    for (int i = 1; i < n; i++) {
        if (inc[i] + dec[i] - 1 > max) {
            max = inc[i] + dec[i] - 1;
        }
    }

    free(inc);
    free(dec);

    return max;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of max length Bitonic Subarray is %d\n", bitonic(arr, n));
    return 0;
}