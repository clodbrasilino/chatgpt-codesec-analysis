#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long find_lcm(const long long *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    long long result = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] == 0) {
            return 0;
        }
        long long common = gcd(result, arr[i]);
        if (arr[i] / common > LLONG_MAX / result) {
            return -1;
        }
        result = (result / common) * arr[i];
    }
    return result;
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n == 0) {
        return EXIT_SUCCESS;
    }
    long long *arr = (long long *)malloc(n * sizeof(long long));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < n; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    long long lcm = find_lcm(arr, n);
    printf("%lld\n", lcm);
    free(arr);
    return EXIT_SUCCESS;
}