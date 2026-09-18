#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_products(const int *arr, int n) {
    long long total = 0;
    long long current = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            if (current > 0 && arr[i] > 0 && current > LLONG_MAX / arr[i]) {
                return LLONG_MAX;
            }
            if (current > 0 && arr[i] < 0 && arr[i] < LLONG_MIN / current) {
                return LLONG_MIN;
            }
            if (current < 0 && arr[i] > 0 && current < LLONG_MIN / arr[i]) {
                return LLONG_MIN;
            }
            if (current < 0 && arr[i] < 0 && arr[i] < LLONG_MAX / current) {
                return LLONG_MAX;
            }
        }
        current *= arr[i];
        if (total > 0 && current > 0 && total > LLONG_MAX - current) {
            return LLONG_MAX;
        }
        if (total < 0 && current < 0 && total < LLONG_MIN - current) {
            return LLONG_MIN;
        }
        total += current;
    }
    return total;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    long long result = sum_of_products(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}