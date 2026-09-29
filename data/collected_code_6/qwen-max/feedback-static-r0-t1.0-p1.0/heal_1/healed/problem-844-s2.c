#include <stdio.h>
#include <stdlib.h>

int findKthElement(int *arr, int n, int k) {
    if (k > n) return -1;
    int oddCount = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 != 0) {
            oddCount++;
        }
    }
    if (k <= oddCount) {
        for (int i = 0; i < n; ++i) {
            if (arr[i] % 2 != 0) {
                k--;
                if (k == 0) {
                    return arr[i];
                }
            }
        }
    } else {
        k -= oddCount;
        for (int i = 0; i < n; ++i) {
            if (arr[i] % 2 == 0) {
                k--;
                if (k == 0) {
                    return arr[i];
                }
            }
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 2, 4, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    int result = findKthElement(arr, n, k);
    if (result != -1) {
        printf("The %dth element is: %d\n", k, result);
    } else {
        printf("Invalid k value or array is empty.\n");
    }
    return 0;
}