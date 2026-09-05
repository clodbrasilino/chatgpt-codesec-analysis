#include <stdio.h>
#include <limits.h>

int min_jumps(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (arr[0] == 0) {
        return -1;
    }

    int jumps = 0;
    int current_end = 0;
    int farthest = 0;

    for (int i = 0; i < n - 1; i++) {
        if (i + arr[i] > farthest) {
            farthest = i + arr[i];
        }
        if (i == current_end) {
            jumps++;
            current_end = farthest;
            if (current_end >= n - 1) {
                break;
            }
        }
    }

    if (current_end < n - 1) {
        return -1;
    }
    return jumps;
}

int main(void) {
    int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result = min_jumps(arr, n);

    if (result == -1) {
        printf("Not reachable\n");
    } else {
        printf("Minimum jumps: %d\n", result);
    }

    return 0;
}