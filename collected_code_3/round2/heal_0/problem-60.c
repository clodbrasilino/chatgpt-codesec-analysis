#include <stdio.h>

int maxLenSub(int arr[], int n) {
    int max_len = 1;
    int len = 1;
    for (int i=0; i<n-1; i++) {
        if (arr[i+1] - arr[i] == 1) {
            len++;
        } else {
            if (max_len < len) {
                max_len = len;
            }
            len = 1;
        }
    }
    if (max_len < len) {
        max_len = len;
    }
    return max_len;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Length of max length subsequence is %d\n", maxLenSub(arr, n));
    return 0;
}