#include <stdio.h>
#include <stdlib.h>

int maxSumNonConsecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return (arr[0] > arr[1]) ? arr[0] : arr[1];

    int incl = arr[0];
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return ((incl > excl) ? incl : excl);
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum sum is %d\n", maxSumNonConsecutive(arr, n));
    return 0;
}