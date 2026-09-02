#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int min_jumps(int arr[], int n) {
    if (n <= 1) return 0;
    if (arr[0] == 0) return -1;

    int jumps = 1;
    int farthest = arr[0];
    int current_end = arr[0];

    for (int i = 1; i < n; i++) {
        if (i == n - 1) return jumps;

        if (i + arr[i] > farthest) {
            farthest = i + arr[i];
        }

        if (i == current_end) {
            jumps++;
            current_end = farthest;

            if (current_end >= n - 1) return jumps;

            if (current_end <= i) return -1;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = min_jumps(arr, n);

    if (result == -1) {
        printf("Cannot reach the end of the array\n");
    } else {
        printf("Minimum jumps required: %d\n", result);
    }

    return 0;
}