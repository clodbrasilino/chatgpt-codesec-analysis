#include <stdio.h>
#include <limits.h>

int max_subarray_sum_length(const int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int best_length = 0;

    for (int i = 0; i < n; i++) {
        int current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += arr[j];
            int current_length = j - i + 1;

            if (current_sum > max_sum) {
                max_sum = current_sum;
                best_length = current_length;
            } else if (current_sum == max_sum) {
                if (current_length < best_length) {
                    best_length = current_length;
                }
            }
        }
    }

    return best_length;
}

int main() {
    int arr[] = {1, -2, 1, 1, -2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = max_subarray_sum_length(arr, n);

    printf("%d\n", length);

    return 0;
}