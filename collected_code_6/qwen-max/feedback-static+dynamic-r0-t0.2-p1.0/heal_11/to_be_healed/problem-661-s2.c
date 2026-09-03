#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5013, got 6000
  *  test case 2 failed: expected 27, got 10
  *  test case 0 failed: expected 2101, got 1200
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];
    if (n == 3) return (arr[0] + arr[1] > arr[0] + arr[2]) ? arr[0] + arr[1] : arr[0] + arr[2];

    int incl = arr[0], excl = 0, excl_new = 0;

    for (int i = 1; i < n; i++) {
        if (i == 1) {
            excl_new = (incl > excl + arr[i]) ? incl : excl + arr[i];
            continue;
        }
        int temp = incl;
        incl = excl_new + arr[i];
        excl_new = (temp > excl) ? temp : excl;
        excl = temp;
    }

    return (incl > excl_new) ? incl : excl_new;
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