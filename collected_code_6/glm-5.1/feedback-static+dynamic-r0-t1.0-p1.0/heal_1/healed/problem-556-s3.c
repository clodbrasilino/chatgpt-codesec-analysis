#include <stdio.h>
#include <stdlib.h>

long long count_odd_xor_pairs(const int *arr, int n) {
    if (arr == NULL || n < 2) {
        return 0;
    }

    long long even = 0;
    long long odd = 0;

    for (int i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even++;
        } else {
            odd++;
        }
    }

    return even * odd;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0) {
        return 1;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    long long result = count_odd_xor_pairs(arr, n);
    printf("%lld\n", result);

    free(arr);
    return 0;
}