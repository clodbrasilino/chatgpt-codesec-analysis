#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceLength(int arr[], int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int *up = (int*)malloc(n * sizeof(int));
    int *down = (int*)malloc(n * sizeof(int));

    if (up == NULL || down == NULL) {
        free(up);
        free(down);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        up[i] = 1;
        down[i] = 1;
    }

    int maxLen = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && up[i] < down[j] + 1) {
                up[i] = down[j] + 1;
            }
            if (arr[i] < arr[j] && down[i] < up[j] + 1) {
                down[i] = up[j] + 1;
            }
        }
        if (up[i] > maxLen) maxLen = up[i];
        if (down[i] > maxLen) maxLen = down[i];
    }

    free(up);
    free(down);
    return maxLen;
}

int main() {
    int arr[] = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxSubsequenceLength(arr, n);

    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}