#include <stdio.h>
#include <stdlib.h>

int longestSeqLength(int *arr, int n) {
    if (n <= 1) return n;

    int *diff = malloc(sizeof(int) * (n - 1));
    for (int i = 0; i < n - 1; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'diff' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        diff[i] = arr[i + 1] - arr[i];
    }

    int count = 1, maxLen = 1;

    for (int i = 1; i < n - 1; i++) {
        if (diff[i] * diff[i - 1] < 0) {
            count++;
            if (count > maxLen) maxLen = count;
        } else {
            count = 1;
        }
    }

    free(diff);

    return maxLen;
}

int main() {
    int arr[] = {10, 22, 9, 33, 49, 50, 31, 60};
    int n = sizeof(arr) / sizeof(arr[0]);
    int length = longestSeqLength(arr, n);
    printf("Length of maximum length subsequence is %d\n", length);
    return 0;
}