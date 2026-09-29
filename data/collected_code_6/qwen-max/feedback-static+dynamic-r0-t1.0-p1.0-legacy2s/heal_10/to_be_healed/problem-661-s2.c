#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2101, got 1000
  *  test case 1 failed: expected 5013, got 4000
  *  test case 2 failed: expected 27, got 6
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int prev1 = arr[0], prev2 = 0, prev3 = 0;

    for (int i = 1; i < n; i++) {
        int exclude = (i - 2 >= 0) ? prev3 : 0;
        int new_prev1 = arr[i] + exclude;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = (new_prev1 > prev1) ? new_prev1 : prev1;
    }

    return prev1;
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum is %d\n", result);

    return 0;
}