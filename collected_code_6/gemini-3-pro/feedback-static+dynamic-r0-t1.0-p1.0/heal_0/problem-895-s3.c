#include <stdio.h>
#include <stdlib.h>

long long findMaxSum(const int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    if (n == 1) {
        return arr[0] > 0 ? arr[0] : 0;
    }

    long long incl = arr[0] > 0 ? arr[0] : 0;
    long long excl = 0;
    long long excl_new;

    for (size_t i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;

        if (arr[i] > 0) {
            incl = excl + arr[i];
        } else {
            incl = excl;
        }

        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main(void) {
    int arr[] = {5, 5, 10, 100, 10, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long max_sum = findMaxSum(arr, n);

    printf("%lld\n", max_sum);

    return 0;
}