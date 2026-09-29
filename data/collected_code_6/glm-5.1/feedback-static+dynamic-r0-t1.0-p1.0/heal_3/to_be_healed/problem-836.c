#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

int max_subarray_sum_length(const int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int best_length = 0;
    int start = 0;
    int current_sum = 0;

    for (int i = 0; i < n; i++) {
        if (current_sum <= 0) {
            current_sum = arr[i];
            start = i;
        } else {
            current_sum += arr[i];
        }

        int current_length = i - start + 1;

        if (current_sum > max_sum) {
            max_sum = current_sum;
            best_length = current_length;
        } else if (current_sum == max_sum) {
            if (current_length < best_length) {
                best_length = current_length;
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