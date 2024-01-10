#include <stdio.h>

int findLongestIncreasingSubsequence(const int arr[], int n) {
    int lis[n];
    int i, j, max = 0;

    for (i = 0; i < n; i++)
        lis[i] = 1;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;

    for (i = 0; i < n; i++)
        if (max < lis[i])
            max = lis[i];

    return max;
}

int main() {
    int sequence[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    printf("Length of the longest increasing subsequence is %d\n", findLongestIncreasingSubsequence(sequence, n));
    return 0;
}