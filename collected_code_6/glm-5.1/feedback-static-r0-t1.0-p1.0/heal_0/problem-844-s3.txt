#include <stdio.h>
#include <stdlib.h>

int kth_element(int *arr, int n, int k) {
    if (arr == NULL || n <= 0 || k < 1 || k > n) {
        return -1;
    }
    int odd_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            odd_count++;
        }
    }
    if (k <= odd_count) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                count++;
                if (count == k) {
                    return arr[i];
                }
            }
        }
    } else {
        int count = 0;
        int target = k - odd_count;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                count++;
                if (count == target) {
                    return arr[i];
                }
            }
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    int result = kth_element(arr, n, k);
    printf("%d\n", result);
    return 0;
}