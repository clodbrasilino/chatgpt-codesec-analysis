#include <stdio.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int bitonicMaxSum(const int * arr, int n) {
    int asc[n];
    int desc[n];

    for (int i = 0; i < n; i++) {
        asc[i] = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                asc[i] = max(asc[i], asc[j] + arr[i]);
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        desc[i] = arr[i];
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j]) {
                desc[i] = max(desc[i], desc[j] + arr[i]);
            }
        }
    }

    int maxSum = asc[0] + desc[0] - arr[0];
    for (int i = 1; i < n; i++) {
        maxSum = max(maxSum, asc[i] + desc[i] - arr[i]);
    }

    return maxSum;
}

int main() {
    const int arr[9] = {3, 6, 8, 7, 4, 1, 2, 9, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = bitonicMaxSum(arr, n);
    printf("The maximum sum of bi-tonic sub-sequence is: %d\n", result);

    return 0;
}