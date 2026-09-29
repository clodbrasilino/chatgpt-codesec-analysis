#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findThreeClosest(int *arr1, int n1, int *arr2, int n2, int *arr3, int n3, int *res) {
    int i = 0, j = 0, k = 0;
    int diff = INT_MAX;
    int p, q, r;

    while (i < n1 && j < n2 && k < n3) {
        int min_diff = abs(arr1[i] - arr2[j]) + abs(arr2[j] - arr3[k]) + abs(arr3[k] - arr1[i]);
        if (min_diff < diff) {
            diff = min_diff;
            p = i, q = j, r = k;
        }

        int max_val = (arr1[i] > arr2[j]) ? arr1[i] : arr2[j];
        max_val = (max_val > arr3[k]) ? max_val : arr3[k];

        if (max_val == arr1[i]) i++;
        else if (max_val == arr2[j]) j++;
        else k++;
    }

    res[0] = arr1[p], res[1] = arr2[q], res[2] = arr3[r];
    return diff;
}

int main() {
    int arr1[] = {1, 4, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {2, 15, 20};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {10, 12};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    int res[3];
    int min_diff = findThreeClosest(arr1, n1, arr2, n2, arr3, n3, res);
    printf("The three closest elements are: %d, %d, and %d with difference %d\n", res[0], res[1], res[2], min_diff);

    return 0;
}