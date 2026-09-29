#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = 0, excl_new, excl, excl2;
    excl = arr[0];
    excl2 = 0;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl ? incl : excl);
        incl = excl2 + arr[i];
        excl2 = excl;
        excl = excl_new;
    }

    return ((incl > excl) ? incl : excl);
}

int main() {
    int test_cases[][7] = {{1200, 800, 200, 150, 300, 900, 400}, {10, 15, 11, 8, 60, 55, 4, 300}, {1, 2, 3, 4, 5, 6, 7}};
    int n[] = {7, 8, 7};
    int expected[] = {2101, 5013, 27};

    for (int j = 0; j < 3; j++) {
        int result = max_sum_no_three_consecutive(test_cases[j], n[j]);
        printf("%d\n", result);
    }

    return 0;
}