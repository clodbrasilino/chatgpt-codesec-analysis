#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int countDistinctPairs(int *arr, int n, int k) {
    qsort(arr, n, sizeof(int), compare);
    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] - arr[i] == k) {
                count++;
                break;
            }
            if (arr[j] - arr[i] > k) break;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 5, 3, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = countDistinctPairs(arr, n, k);
    printf("Number of distinct pairs with difference %d: %d\n", k, result);
    return 0;
}