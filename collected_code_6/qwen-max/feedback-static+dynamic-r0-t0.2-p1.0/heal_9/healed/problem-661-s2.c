#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int excl_new = 0, incl = arr[0], excl = 0;

    for (int i = 1; i < n; i++) {
        int tmp = excl_new;
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = tmp;

        if (i >= 3) {
            incl = excl_new + arr[i];
            excl = (tmp > excl_new) ? tmp : excl_new;
        }
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