#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5013, got 6000
  *  test case 0 failed: expected 2101, got 1200
  *  test case 2 failed: expected 27, got 10
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int arr[] = {12, 34, 15, 20, 30, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", result);
    return 0;
}