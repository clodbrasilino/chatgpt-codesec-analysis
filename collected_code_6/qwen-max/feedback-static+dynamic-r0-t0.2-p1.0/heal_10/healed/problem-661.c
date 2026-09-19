#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int prev3 = 0, prev2 = arr[0], prev1 = arr[0] + arr[1];

    for (int i = 2; i < n; i++) {
        int incl = arr[i] + prev3;
        int excl = prev1;
        int new_max = (incl > excl) ? incl : excl;

        prev3 = ((prev2 > prev1) ? prev2 : prev1 - arr[i-1]);
        prev2 = prev1;
        prev1 = new_max;
    }

    return prev1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum with no three consecutive elements: %d\n", result);
    return 0;
}