#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t binomial_coefficient(int64_t n, int64_t k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    int64_t result = 1;
    for (int64_t i = 0; i < k; i++) {
        if (result > INT64_MAX / (n - i)) {
            return -1;
        }
        result = result * (n - i) / (i + 1);
    }
    return result;
}

int64_t sum_of_squares(int64_t n) {
    if (n < 0) {
        return -1;
    }
    int64_t sum = 0;
    for (int64_t k = 0; k <= n; k++) {
        int64_t coeff = binomial_coefficient(n, k);
        if (coeff == -1 || coeff > INT64_MAX / coeff) {
            return -1;
        }
        int64_t square = coeff * coeff;
        if (sum > INT64_MAX - square) {
            return -1;
        }
        sum += square;
    }
    return sum;
}

int main(void) {
    int64_t n;
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    int64_t result = sum_of_squares(n);
    if (result == -1) {
        return 1;
    }
    printf("%" PRId64 "\n", result);
    return 0;
}