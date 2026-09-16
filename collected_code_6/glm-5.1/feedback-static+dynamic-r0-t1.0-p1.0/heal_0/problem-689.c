#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minJumps(int *arr, int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (arr[0] == 0) {
        return -1;
    }
    int *jumps = (int *)malloc(n * sizeof(int));
    if (jumps == NULL) {
        return -1;
    }
    jumps[0] = 0;
    for (int i = 1; i < n; i++) {
        jumps[i] = INT_MAX;
        for (int j = 0; j < i; j++) {
            if (jumps[j] != INT_MAX && i <= j + arr[j]) {
                if (jumps[j] + 1 < jumps[i]) {
                    jumps[i] = jumps[j] + 1;
                }
            }
        }
        if (jumps[i] == INT_MAX) {
            free(jumps);
            return -1;
        }
    }
    int result = jumps[n - 1];
    free(jumps);
    return result;
}

int main() {
    int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int res = minJumps(arr, n);
    printf("%d\n", res);
    return 0;
}