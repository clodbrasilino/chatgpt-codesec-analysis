#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 27, got 6
  *  test case 1 failed: expected 5013, got 4000
  *  test case 0 failed: expected 2101, got 1000
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl_new = 0;
    int excl_old = 0;

    for (int i = 1; i < n; i++) {
        int temp = excl_new;
        excl_new = (incl > excl_new) ? incl : excl_new;
        incl = excl_old + arr[i];
        excl_old = temp;
    }

    return (incl > excl_new) ? incl : excl_new;
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", max_sum_no_three_consecutive(arr, n));
    return 0;
}