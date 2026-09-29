#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5013, got 12000
  *  test case 0 failed: expected 2101, got 1400
  *  test case 2 failed: expected 27, got 33
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl = 0;

    for (int i = 1; i < n; i++) {
        int excl_new = (incl > excl) ? incl : excl;
        if (i < 3) {
            incl = excl + arr[i];
        } else {
            incl = excl + arr[i] + ((excl_new > (excl - arr[i-2])) ? (excl_new - arr[i-2]) : (excl - arr[i-2]));
        }
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int test0[] = {1, 2, 3, 1, 5, 6, 8};
    int test1[] = {3, 4, 5, 1, 2, 3, 10, 1, 2, 3, 10, 1, 2, 3, 10};
    int test2[] = {1, 2, 3, 4, 5};

    int n0 = sizeof(test0) / sizeof(test0[0]);
    int n1 = sizeof(test1) / sizeof(test1[0]);
    int n2 = sizeof(test2) / sizeof(test2[0]);

    printf("Test 0: Maximum sum is %d\n", max_sum_no_three_consecutive(test0, n0));
    printf("Test 1: Maximum sum is %d\n", max_sum_no_three_consecutive(test1, n1));
    printf("Test 2: Maximum sum is %d\n", max_sum_no_three_consecutive(test2, n2));

    return 0;
}