#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int* lis(int arr[], int n) {
    int *lis = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        lis[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    return lis;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int* lds(int arr[], int n) {
    int *lds = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        lds[i] = 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }
    return lds;
}

int longestBitonicSubsequence(int arr[], int n) {
    int *inc = lis(arr, n);
    int *dec = lds(arr, n);
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        max_length = max(max_length, inc[i] + dec[i] - 1);
    }
    free(inc);
    free(dec);
    return max_length;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of longest bitonic subsequence is %d\n", longestBitonicSubsequence(arr, n));
    return 0;
}