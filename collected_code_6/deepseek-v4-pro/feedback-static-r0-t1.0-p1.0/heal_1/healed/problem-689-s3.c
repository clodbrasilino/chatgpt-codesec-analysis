#include <stdio.h>
#include <limits.h>

int min_jumps(const int arr[], int n) {
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
            if (i >= current_end) return -1;
        }
    }

    return -1;
}

int main(void) {
    int arr1[] = {2, 3, 1, 1, 2, 4, 2, 0, 1, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", min_jumps(arr1, n1));

    int arr2[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", min_jumps(arr2, n2));

    int arr3[] = {1, 0, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", min_jumps(arr3, n3));

    int arr4[] = {1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", min_jumps(arr4, n4));

    int arr5[] = {0, 1};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", min_jumps(arr5, n5));

    return 0;
}