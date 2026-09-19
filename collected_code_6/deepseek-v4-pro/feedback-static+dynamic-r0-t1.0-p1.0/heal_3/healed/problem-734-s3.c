#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            if (arr[j] > 0) {
                if (product > LLONG_MAX / arr[j]) {
                    if (total > 0) {
                        return LLONG_MAX;
                    }
                    product = 1;
                    continue;
                }
            } else if (arr[j] < 0) {
                if (arr[j] == -1 && product == LLONG_MIN) {
                    if (total <= 0) {
                        return LLONG_MIN;
                    }
                    product = 1;
                    continue;
                }
                if (product > 0) {
                    if (product > LLONG_MAX / (-arr[j])) {
                        if ((long long)arr[j] * product < 0) {
                            if (total <= 0) {
                                return LLONG_MIN;
                            }
                            product = 1;
                            continue;
                        }
                    }
                }
            }
            product *= arr[j];
            if (product > 0 && total > LLONG_MAX - product) {
                return LLONG_MAX;
            }
            if (product < 0 && total < LLONG_MIN - product) {
                return LLONG_MIN;
            }
            total += product;
        }
    }
    return total;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
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
    long long result = sum_of_products_of_subarrays(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}