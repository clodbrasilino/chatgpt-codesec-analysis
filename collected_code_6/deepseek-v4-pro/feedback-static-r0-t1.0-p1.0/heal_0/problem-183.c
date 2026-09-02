#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int countPairsWithDifference(int arr[], int n, int k) {
    if (n < 2 || k < 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare);

    int count = 0;
    int i = 0;
    int j = 1;

    while (j < n) {
        int diff = arr[j] - arr[i];

        if (diff == k) {
            count++;
            int left_val = arr[i];
            int right_val = arr[j];

            while (i < n && arr[i] == left_val) {
                i++;
            }
            while (j < n && arr[j] == right_val) {
                j++;
            }
        } else if (diff < k) {
            j++;
        } else {
            i++;
            if (i == j) {
                j++;
            }
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 5, 3, 4, 2, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    int result = countPairsWithDifference(arr, n, k);
    printf("%d\n", result);

    int arr2[] = {8, 12, 16, 4, 0, 20};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 4;

    int result2 = countPairsWithDifference(arr2, n2, k2);
    printf("%d\n", result2);

    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 1;

    int result3 = countPairsWithDifference(arr3, n3, k3);
    printf("%d\n", result3);

    return 0;
}