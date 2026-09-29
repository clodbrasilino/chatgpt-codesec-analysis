#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int countDistinctPairsWithDifferenceK(int arr[], int n, int k) {
    if (arr == NULL || n <= 0 || k < 0) {
        return 0;
    }

    int count = 0;
    int left = 0;
    int right = 0;

    qsort(arr, n, sizeof(int), compare);

    while (right < n) {
        if (left == right) {
            right++;
        } else if (arr[right] - arr[left] == k) {
            count++;
            left++;
            right++;

            while (left < n && arr[left] == arr[left - 1]) left++;
            while (right < n && arr[right] == arr[right - 1]) right++;
        } else if (arr[right] - arr[left] < k) {
            right++;
        } else {
            left++;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 5, 3, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = countDistinctPairsWithDifferenceK(arr, n, k);
    printf("%d\n", result);

    int arr2[] = {8, 12, 16, 4, 0, 20};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 4;

    int result2 = countDistinctPairsWithDifferenceK(arr2, n2, k2);
    printf("%d\n", result2);

    int arr3[] = {1, 1, 1, 1, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 0;

    int result3 = countDistinctPairsWithDifferenceK(arr3, n3, k3);
    printf("%d\n", result3);

    return 0;
}