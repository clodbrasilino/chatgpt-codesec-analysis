#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int prev2 = arr[0], prev1 = arr[1], mx = prev2;

    for (int i = 2; i < n; i++) {
        int incl = arr[i] + prev2;
        int excl = prev1;
        int new_max = (incl > excl) ? incl : excl;
        prev2 = prev1;
        prev1 = new_max;
        mx = (mx > new_max) ? mx : new_max;
    }

    return mx;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("Maximum sum with no three consecutive elements: %d\n", result);
    return 0;
}