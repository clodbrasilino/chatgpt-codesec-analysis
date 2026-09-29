#include <stdio.h>
#include <stdlib.h>

int min_jumps(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (arr[0] <= 0) {
        return -1;
    }

    int jumps = 1;
    int farthest = arr[0];
    int current_end = arr[0];

    for (int i = 1; i < n; i++) {
        if (i == n - 1) {
            return jumps;
        }

        if (i + arr[i] > farthest) {
            farthest = i + arr[i];
        }

        if (i == current_end) {
            jumps++;
            if (farthest <= i) {
                return -1;
            }
            current_end = farthest;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {2, 3, 1, 1, 4};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    int result = min_jumps(arr, n);
    if (result >= 0) {
        printf("Minimum number of jumps: %d\n", result);
    } else {
        printf("End is unreachable\n");
    }

    return 0;
}