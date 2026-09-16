#include <stdio.h>
#include <limits.h>

int find_sum_of_first_even_odd(const int *arr, int n, int *sum_even, int *sum_odd) {
    *sum_even = INT_MAX;
    *sum_odd = INT_MAX;

    for (int i = 0; i < n; ++i) {
        if (*sum_even == INT_MAX && arr[i] % 2 == 0) {
            *sum_even = arr[i];
        }
        if (*sum_odd == INT_MAX && arr[i] % 2 != 0) {
            *sum_odd = arr[i];
        }
        if (*sum_even != INT_MAX && *sum_odd != INT_MAX) {
            break;
        }
    }

    return *sum_even != INT_MAX && *sum_odd != INT_MAX;
}

int main() {
    int arr[] = {1, 3, 5, 8, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum_even, sum_odd;

    if (find_sum_of_first_even_odd(arr, n, &sum_even, &sum_odd)) {
        printf("Sum of first even and odd numbers: %d\n", sum_even + sum_odd);
    } else {
        printf("First even and odd numbers not found.\n");
    }

    return 0;
}