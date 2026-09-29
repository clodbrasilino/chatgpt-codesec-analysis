#include <stdio.h>
#include <limits.h>

int max_subarray_length(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int curr_sum = 0;
    int best_length = 0;
    int curr_length = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        curr_sum += arr[i];
        curr_length++;

        if (curr_sum > max_sum) {
            max_sum = curr_sum;
            best_length = curr_length;
        }

        if (curr_sum < 0) {
            curr_sum = 0;
            curr_length = 0;
        }
    }

    if (best_length == 0) {
        int max_val = arr[0];
        best_length = 1;
        for (int i = 1; i < n; i++) {
            if (arr[i] > max_val) {
                max_val = arr[i];
                best_length = 1;
            }
        }
    }

    return best_length;
}

int main(void) {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = max_subarray_length(arr, n);
    printf("%d\n", result);

    return 0;
}