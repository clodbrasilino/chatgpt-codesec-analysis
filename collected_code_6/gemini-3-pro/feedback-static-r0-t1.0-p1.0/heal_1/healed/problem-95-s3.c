#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_sublist_length(const int *arr, int n, int target) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int min_len = INT_MAX;
    int current_sum = 0;
    int start = 0;

    for (int end = 0; end < n; end++) {
        current_sum += arr[end];

        while (current_sum > target && start <= end) {
            if (end - start + 1 < min_len) {
                min_len = end - start + 1;
            }
            current_sum -= arr[start];
            start++;
        }
    }

    return (min_len == INT_MAX) ? 0 : min_len;
}

int main(void) {
    int arr[] = {1, 4, 45, 6, 0, 19};
    int target = 51;
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = find_min_sublist_length(arr, n, target);
    
    printf("%d\n", result);

    return 0;
}