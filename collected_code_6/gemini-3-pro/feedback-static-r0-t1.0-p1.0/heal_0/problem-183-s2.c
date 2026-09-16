#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int countDistinctPairs(int *arr, int n, int k) {
    if (arr == NULL || n < 2 || k < 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare);

    int count = 0;
    int left = 0;
    int right = 1;

    while (right < n) {
        int diff = arr[right] - arr[left];

        if (diff == k) {
            count++;
            left++;
            right++;

            while (left < n && arr[left] == arr[left - 1]) {
                left++;
            }
            while (right < n && arr[right] == arr[right - 1]) {
                right++;
            }
        } else if (diff < k) {
            right++;
        } else {
            left++;
        }

        if (left == right) {
            right++;
        }
    }

    return count;
}

int main() {
    int arr[] = {1, 5, 3, 4, 2, 2, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = countDistinctPairs(arr, n, k);
    printf("%d\n", result);

    return 0;
}