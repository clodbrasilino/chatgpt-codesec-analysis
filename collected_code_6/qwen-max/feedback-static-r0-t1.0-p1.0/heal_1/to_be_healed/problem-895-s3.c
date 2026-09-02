#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSum(int arr[], int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    int incl = arr[0];
    int excl = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'excl_new' can be reduced. [variableScope]
     */
    int excl_new;
    for (int i = 1; i < n; i++) {
        excl_new = max(incl, excl);
        incl = excl + arr[i];
        excl = excl_new;
    }
    return max(incl, excl);
}

int main() {
    int arr[] = {5, 5, 10, 100, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum sum of non-adjacent elements: %d\n", findMaxSum(arr, n));
    return 0;
}