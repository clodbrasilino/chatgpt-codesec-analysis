#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int countDistinctPairsWithDiffK(int arr[], int n, int k) {
    if (arr == NULL || n <= 1 || k < 0) {
        return 0;
    }

    qsort(arr, (size_t)n, sizeof(int), compare);

    int count = 0;
    int left = 0;
    int right = 1;

    while (right < n) {
        int diff = arr[right] - arr[left];

        if (diff == k) {
            count++;
            int leftVal = arr[left];
            int rightVal = arr[right];
            while (left < n && arr[left] == leftVal) left++;
            while (right < n && arr[right] == rightVal) right++;
        } else if (diff < k) {
            right++;
        } else {
            left++;
            if (left == right) {
                right++;
            }
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 5, 3, 4, 2, 5, 3};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int k = 2;

    int result = countDistinctPairsWithDiffK(arr, n, k);
    printf("Number of distinct pairs with difference %d: %d\n", k, result);

    return 0;
}