#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int incl = arr[0];
    int excl = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'excl_new' can be reduced. [variableScope]
     */
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int arr[] = {12, 34, 15, 20, 30, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", result);
    return 0;
}