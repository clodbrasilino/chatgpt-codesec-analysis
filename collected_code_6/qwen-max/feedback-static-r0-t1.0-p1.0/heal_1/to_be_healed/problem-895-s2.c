#include <stdio.h>
#include <stdlib.h>

int max_sum_subseq(int* nums, int n) {
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int incl = nums[0];
    int excl = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'excl_new' can be reduced. [variableScope]
     */
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + nums[i];
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main() {
    int arr[] = {5, 5, 10, 100, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum sum of non-adjacent elements is: %d\n", max_sum_subseq(arr, n));
    return 0;
}