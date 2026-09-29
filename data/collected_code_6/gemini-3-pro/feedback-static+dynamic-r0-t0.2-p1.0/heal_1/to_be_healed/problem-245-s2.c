/* Possible weaknesses found:
 *  expected '>'
 *  stdio.: No such file or directory
 *  to match this '<'
 *  No pair for character (<). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
 *  missing terminating '>' character
 */
#include <stdio.
#include <stdlib.h>

int maxSumBitonicSubsequence(int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int *msis = (int *)malloc(n * sizeof(int));
    int *msds = (int *)malloc(n * sizeof(int));

    if (msis == NULL || msds == NULL) {
        free(msis);
        free(msds);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        msis[i] = arr[i];
        msds[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && msds[i] < msds[j] + arr[i]) {
                msds[i] = msds[j] + arr[i];
            }
        }
    }

    int max_sum = msis[0] + msds[0] - arr[0];
    for (int i = 1; i < n; i++) {
        if (msis[i] + msds[i] - arr[i] > max_sum) {
            max_sum = msis[i] + msds[i] - arr[i];
        }
    }

    free(msis);
    free(msds);

    return max_sum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxSumBitonicSubsequence(arr, n);
    if (result != -1) {
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        printf("Maximum sum of bitonic subsequence is %d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}