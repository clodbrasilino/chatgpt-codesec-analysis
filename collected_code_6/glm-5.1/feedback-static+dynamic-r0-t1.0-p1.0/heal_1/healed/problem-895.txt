#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max_sum_no_adjacent(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    if (n == 1) {
        return max(0, arr[0]);
    }

    int prev2 = max(0, arr[0]);
    int prev1 = max(prev2, arr[1]);

    for (int i = 2; i < n; i++) {
        int current = max(prev1, prev2 + arr[i]);
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

int main(void) {
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", max_sum_no_adjacent(arr1, n1));

    int arr2[] = {3, 2, 7, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", max_sum_no_adjacent(arr2, n2));

    int arr3[] = {3, 2, 5, 10, 7};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", max_sum_no_adjacent(arr3, n3));

    int arr4[] = {-1, -2, -3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", max_sum_no_adjacent(arr4, n4));

    return 0;
}