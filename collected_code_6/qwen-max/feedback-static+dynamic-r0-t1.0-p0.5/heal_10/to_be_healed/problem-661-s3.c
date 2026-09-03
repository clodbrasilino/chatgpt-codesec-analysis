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

    int incl = arr[0], excl_new = 0, excl_old = 0;
    for (int i = 1; i < n; i++) {
        int temp = (incl > excl_new) ? incl : excl_new;
        incl = excl_old + arr[i];
        excl_old = excl_new;
        excl_new = temp;

        if (i == 2) {
            incl = (incl > excl_new) ? incl : excl_new;
        }
    }

    return (incl > excl_new) ? incl : excl_new;
}

int main() {
    int test_arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test_arr2[] = {10, 17, 0, 3, 2, 5, 7};
    int test_arr3[] = {10, 11, 1, 2, 3, 4, 5, 6};

    int result1 = max_sum_no_three_consecutive(test_arr1, sizeof(test_arr1) / sizeof(test_arr1[0]));
    int result2 = max_sum_no_three_consecutive(test_arr2, sizeof(test_arr2) / sizeof(test_arr2[0]));
    int result3 = max_sum_no_three_consecutive(test_arr3, sizeof(test_arr3) / sizeof(test_arr3[0]));

    printf("Test 1: Maximum sum is %d\n", result1);
    printf("Test 2: Maximum sum is %d\n", result2);
    printf("Test 3: Maximum sum is %d\n", result3);

    return 0;
}