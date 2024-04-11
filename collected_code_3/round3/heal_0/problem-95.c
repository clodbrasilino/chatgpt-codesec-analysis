#include <stdio.h>
#include <limits.h>

int findMinLength(int arr[], int n, int x) {
    int start = 0, end = 0;
    int min_len = INT_MAX, curr_sum = 0;

    while (end < n) {
        while (curr_sum <= x && end < n)
            curr_sum += arr[end++];

        while (curr_sum > x && start < n) {
            if (end - start < min_len)
                min_len = end - start;

            curr_sum -= arr[start++];
        }
    }
    return min_len;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 19};
    int x = 51;
    int n = sizeof(arr) / sizeof(arr[0]);
    int res = findMinLength(arr, n, x);
    printf("Minimum length of sublist is %d\n", res);
    return 0;
}