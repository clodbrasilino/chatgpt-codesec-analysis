#include <stdio.h>

int maxLenSub(int arr[], int n, int diff) {
    int maxLen = 1;
    int currLen = 1;

    for (int i=1; i<n; i++) {
        if (arr[i] - arr[i-1] == diff) {
            currLen++;
        } else {
            if (currLen > maxLen) {
                maxLen = currLen;
            }
            currLen = 1;
        }
    }

    if (currLen > maxLen) {
        maxLen = currLen;
    }

    return maxLen;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    int diff = 1;
    printf("Max length of subsequence with difference %d is %d\n", diff, maxLenSub(arr, n, diff));
    return 0;
}