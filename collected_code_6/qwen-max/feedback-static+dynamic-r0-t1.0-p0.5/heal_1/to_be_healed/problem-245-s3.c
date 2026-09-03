#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int* calculate_max_sum(int arr[], int n, int *max_sum) {
    int *msis = (int*)malloc(n * sizeof(int));
    if (msis == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++) msis[i] = arr[i];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i])
                msis[i] = msis[j] + arr[i];

    int *msds = (int*)malloc(n * sizeof(int));
    if (msds == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++) msds[i] = arr[i];

    for (int i = n - 2; i >= 0; i--)
        for (int j = n - 1; j > i; j--)
            if (arr[i] > arr[j] && msds[i] < msds[j] + arr[i])
                msds[i] = msds[j] + arr[i];

    *max_sum = 0;
    for (int i = 0; i < n; i++)
        *max_sum = max(*max_sum, msis[i] + msds[i] - arr[i]);

    free(msis);
    return msds;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_sum;
    int *msds = calculate_max_sum(arr, n, &max_sum);
    printf("Maximum sum of bi-tonic sub-sequence: %d\n", max_sum);
    free(msds);
    return 0;
}