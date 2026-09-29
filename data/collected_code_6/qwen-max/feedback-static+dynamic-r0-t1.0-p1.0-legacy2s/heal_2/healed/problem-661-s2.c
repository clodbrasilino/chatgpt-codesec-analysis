#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl = 0;

    for (int i = 1; i < n; i++) {
        int excl_new = excl > incl ? excl : incl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return incl > excl ? incl : excl;
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum is %d\n", result);

    return 0;
}