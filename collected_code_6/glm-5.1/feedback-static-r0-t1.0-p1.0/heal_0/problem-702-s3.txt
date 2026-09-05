#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_min_removals(int arr[], int n, int k) {
    if (n <= 1) {
        return 0;
    }
    qsort(arr, n, sizeof(int), compare);
    int max_len = 1;
    int left = 0;
    for (int right = 0; right < n; right++) {
        while (arr[right] - arr[left] > k) {
            left++;
        }
        int current_len = right - left + 1;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }
    return n - max_len;
}

int main() {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    int result = find_min_removals(arr, n, k);
    printf("%d\n", result);
    return 0;
}