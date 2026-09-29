#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long find_lcm(const long long *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    unsigned long long result;
    if (arr[0] < 0) {
        result = -(unsigned long long)arr[0];
    } else {
        result = arr[0];
    }
    for (size_t i = 1; i < n; i++) {
        long long current = arr[i];
        if (current == 0) {
            return 0;
        }
        unsigned long long ucurrent;
        if (current < 0) {
            ucurrent = -(unsigned long long)current;
        } else {
            ucurrent = current;
        }
        unsigned long long common = gcd(result, ucurrent);
        if (result > ULLONG_MAX / (ucurrent / common)) {
            return -1;
        }
        result = (result / common) * ucurrent;
    }
    return (long long)result;
}

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n == 0) {
        return EXIT_SUCCESS;
    }
    if (n > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
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