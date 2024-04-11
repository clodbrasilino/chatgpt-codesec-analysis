#include <stdio.h>
#include <stdlib.h>

int maxProductIS(int arr[], int n) {
    int *max_product = (int*) malloc (n * sizeof(int));
    int max = 0;
    int i, j;

    for (i = 0; i < n; i++)
        max_product[i] = arr[i];

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && max_product[i] < max_product[j] * arr[i])
                max_product[i] = max_product[j] * arr[i];

    for (i = 0; i < n; i++)
        if (max < max_product[i])
            max = max_product[i];

    free(max_product);

    return max;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum product of an increasing subsequence is %d\n", maxProductIS(arr, n));
    return 0;
}