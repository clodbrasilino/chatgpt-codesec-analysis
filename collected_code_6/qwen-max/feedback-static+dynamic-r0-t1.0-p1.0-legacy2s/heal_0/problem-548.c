#include <stdio.h>
#include <stdlib.h>

int lis(int arr[], int n) {
    if (n == 0) return 0;
    int *lis, i, j, max_lis;
    lis = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        lis[i] = 1;
    }
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    max_lis = 0;
    for (i = 0; i < n; i++) {
        if (max_lis < lis[i]) {
            max_lis = lis[i];
        }
    }
    free(lis);
    return max_lis;
}

int main() {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Length of LIS is %d\n", lis(arr, n));
    return 0;
}