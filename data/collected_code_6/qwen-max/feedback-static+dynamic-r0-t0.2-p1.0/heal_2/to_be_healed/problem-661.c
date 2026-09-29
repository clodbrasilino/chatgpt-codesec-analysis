#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 27, got 10
  *  test case 1 failed: expected 5013, got 6000
  *  test case 0 failed: expected 2101, got 1200
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl = 0;

    for (int i = 1; i < n; i++) {
        int excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum with no three consecutive elements: %d\n", result);
    return 0;
}