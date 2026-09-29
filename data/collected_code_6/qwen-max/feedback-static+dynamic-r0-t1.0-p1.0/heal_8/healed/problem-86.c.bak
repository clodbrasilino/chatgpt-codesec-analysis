#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    int64_t intermediate_result = 3 * n - 3;
    if (intermediate_result > INT64_MAX - n) {
        return -1;
    }
    int64_t result = n + 1;
    int64_t max_safe_value = (INT64_MAX - 1) / n;
    if (intermediate_result > max_safe_value) {
        return -1;
    }
    result += intermediate_result * n;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    }
    return 0;
}