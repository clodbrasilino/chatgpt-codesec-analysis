#include <stdio.h>
#include <limits.h>

int max_subarray_sum_length(const int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int current_sum = 0;
    int start = 0;
    int best_start = 0;
    int best_end = 0;

    for (int i = 0; i < n; i++) {
        if (current_sum <= 0) {
            current_sum = arr[i];
            start = i;
        } else {
            current_sum += arr[i];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            best_start = start;
            best_end = i;
        } else if (current_sum == max_sum) {
            int current_length = i - start + 1;
            int best_length = best_end - best_start + 1;
            if (current_length < best_length) {
                best_start = start;
                best_end = i;
            }
        }
    }

    return best_end - best_start + 1;
}

int main() {
    int arr[] = {1, -2, 1, 1, -2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int length = max_subarray_sum_length(arr, n);
    
    printf("%d\n", length);
    
    return 0;
}