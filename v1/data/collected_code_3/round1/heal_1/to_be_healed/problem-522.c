#include <stdio.h>
#include <stdlib.h>

int longestBitonic(int arr[], int n) {
    int* inc = (int*)malloc(sizeof(int) * n);
    int* dec = (int*)malloc(sizeof(int) * n);
    int i, max;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'inc' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    inc[0] = 1;
    dec[n - 1] = 1;

    for (i = 1; i < n; i++) {
        inc[i] = (arr[i] >= arr[i - 1]) ? inc[i - 1] + 1 : 1;
    }

    for (i = n - 2; i >= 0; i--) {
        dec[i] = (arr[i] >= arr[i + 1]) ? dec[i + 1] + 1 : 1;
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dec' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    max = inc[0] + dec[0] - 1;
    for (i = 1; i < n; i++) {
        if (inc[i] + dec[i] - 1 > max) {
            max = inc[i] + dec[i] - 1;
        }
    }

    free(inc);
    free(dec);

    return max;
}

int main() {
    int arr[] = {12, 4, 78, 90, 45, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of max length Bitonic Subsequence is %d\n", longestBitonic(arr, n));
    return 0;
}