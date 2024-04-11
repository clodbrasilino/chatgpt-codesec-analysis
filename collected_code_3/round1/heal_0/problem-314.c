#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSum(int arr[][2], int n) {
    int incl = max(arr[0][0], arr[0][1]);
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = max(incl, excl);
        incl = excl + max(arr[i][0], arr[i][1]);
        excl = excl_new;
    }

    return max(incl, excl);
}

int main() {
    int arr[][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", findMaxSum(arr, n));
    return 0;
}