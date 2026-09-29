#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2101, got 2100
  *  test case 1 failed: expected 5013, got 8000
  *  test case 2 failed: expected 27, got 10
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];
    if (n == 3) return (arr[0] + arr[2] > arr[1] + arr[2]) ? arr[0] + arr[2] : arr[1] + arr[2];

    int incl = arr[0];
    int excl = 0;

    for (int i = 1; i < n; i++) {
        int excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        if (i >= 2) {
            int temp = excl + arr[i - 2];
            incl = (incl > temp) ? incl : temp;
        }
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int arr[] = {5, 7, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum with no three consecutive elements: %d\n", result);
    return 0;
}