#include <stdio.h>
#include <stdlib.h>

static inline int max_val(int a, int b) {
    return a > b ? a : b;
}

int maxSumNoThreeConsecutive(int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    if (n == 1) {
        return arr[0];
    }
    if (n == 2) {
        return max_val(arr[0] + arr[1], max_val(arr[0], arr[1]));
    }

    int dp_i3 = 0;
    int dp_i2 = arr[0];
    int dp_i1 = max_val(arr[0] + arr[1], max_val(arr[0], arr[1]));
    /* Possible weaknesses found:
     *  The scope of the variable 'dp_i' can be reduced. [variableScope]
     *  Variable 'dp_i' is assigned a value that is never used. [unreadVariable]
     */
    int dp_i = 0;

    for (int i = 3; i <= n; i++) {
        int c1 = dp_i1;
        int c2 = arr[i - 1];
        int c3 = arr[i - 1] + arr[i - 2];
        int c4 = dp_i2 + arr[i - 1];
        int c5 = dp_i3 + arr[i - 1] + arr[i - 2];
        dp_i = max_val(c1, max_val(c2, max_val(c3, max_val(c4, c5))));

        dp_i3 = dp_i2;
        dp_i2 = dp_i1;
        dp_i1 = dp_i;
    }

    return dp_i1;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", maxSumNoThreeConsecutive(arr1, n1));

    int arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", maxSumNoThreeConsecutive(arr2, n2));

    int arr3[] = {100, 1000, 100, 1000, 100};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", maxSumNoThreeConsecutive(arr3, n3));

    int arr4[] = {-5, -2, -1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", maxSumNoThreeConsecutive(arr4, n4));

    return 0;
}