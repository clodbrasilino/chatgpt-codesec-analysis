#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_cubes_minus_sum(int64_t n) {
    if (n < 1) {
        return 0;
    }
    if (n > 28783) {
        int64_t sum = n * (n + 1) / 2;
        int64_t sum_cubes = 0;
        for (int64_t i = 1; i <= n; i++) {
            int64_t term = i * i;
            if (term > INT64_MAX / i) {
                return -1;
            }
            sum_cubes += term * i;
        }
        return sum_cubes - sum;
    }
    int64_t sum = n * (n + 1) / 2;
    int64_t sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int64_t n;
    printf("Enter a positive integer: ");
    if (scanf("%" SCNd64, &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int64_t result = sum_of_cubes_minus_sum(n);
    if (result == -1 && n > 28783) {
        printf("Overflow detected\n");
        return 1;
    }
    printf("%" PRId64 "\n", result);
    return 0;
}