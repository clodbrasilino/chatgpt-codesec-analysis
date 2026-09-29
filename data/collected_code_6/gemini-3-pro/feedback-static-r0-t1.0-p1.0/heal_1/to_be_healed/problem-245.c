#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int maxBitonicSum(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int *MSIS = (int *)malloc(n * sizeof(int));
    if (MSIS == NULL) {
        return -1;
    }

    int *MSDS = (int *)malloc(n * sizeof(int));
    if (MSDS == NULL) {
        free(MSIS);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        MSIS[i] = arr[i];
        MSDS[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && MSIS[i] < MSIS[j] + arr[i]) {
                MSIS[i] = MSIS[j] + arr[i];
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && MSDS[i] < MSDS[j] + arr[i]) {
                MSDS[i] = MSDS[j] + arr[i];
            }
        }
    }

    int maxSum = -1;
    for (int i = 0; i < n; i++) {
        if ((MSIS[i] + MSDS[i] - arr[i]) > maxSum) {
            maxSum = MSIS[i] + MSDS[i] - arr[i];
        }
    }

    free(MSIS);
    free(MSDS);

    return maxSum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxBitonicSum(arr, n);
    if (result != -1) {
        printf("Maximum sum of bi-tonic sub-sequence is %d\n", result);
    } else {
        printf("Memory allocation failed or invalid input\n");
    }

    return 0;
}