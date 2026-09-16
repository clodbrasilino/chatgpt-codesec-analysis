#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2101, got 1200
  *  test case 2 failed: expected 27, got 10
  *  test case 1 failed: expected 5013, got 6000
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] > arr[1] ? arr[0] : arr[1];

    int incl = arr[0];
    int excl = 0;
    int excl_new = 0;

    for (int i = 1; i < n; i++) {
        int temp = excl_new;
        excl_new = excl > incl ? excl : incl;
        incl = temp + arr[i];
        excl = excl_new;
    }

    return incl > excl ? incl : excl;
}

int main() {
    int test_cases[] = {5, 7, 8, 3, 4, 5, 6};
    int n = sizeof(test_cases) / sizeof(test_cases[0]);
    printf("Test case: %d\n", max_sum_no_three_consecutive(test_cases, n));

    int test_case2[] = {10, 15, 1, 2, 3, 20};
    n = sizeof(test_case2) / sizeof(test_case2[0]);
    printf("Test case: %d\n", max_sum_no_three_consecutive(test_case2, n));

    int test_case3[] = {3, 2, 5, 10, 7};
    n = sizeof(test_case3) / sizeof(test_case3[0]);
    printf("Test case: %d\n", max_sum_no_three_consecutive(test_case3, n));

    return 0;
}