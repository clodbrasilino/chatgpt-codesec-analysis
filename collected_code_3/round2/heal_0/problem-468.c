#include <stdio.h>
#include <stdlib.h>

int maxProductIS(int arr[], int n) {
    int max = 0, i, j;
    int maxProduct[n];

    for (i = 0; i < n; i++)
        maxProduct[i] = arr[i];

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && maxProduct[i] < maxProduct[j] * arr[i])
                maxProduct[i] = maxProduct[j] * arr[i];

    for (i = 0; i < n; i++)
        if (max < maxProduct[i])
            max = maxProduct[i];

    return max;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum product of increasing subsequence is %d\n", maxProductIS(arr, n));
    return 0;
}