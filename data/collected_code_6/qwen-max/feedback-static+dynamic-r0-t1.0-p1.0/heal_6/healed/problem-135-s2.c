#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_hexagonal_number(int64_t n) {
    if (n < 1 || n > 3037000499) {
        return -1;
    }
    int64_t max_safe_n = (INT64_MAX / n + 1) / 2;
    if (n > max_safe_n) {
        return -1;
    }
    int64_t result = n * (2 * n - 1);
    if (result / n != 2 * n - 1) {
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) == 1 && n > 0) {
        int64_t hex_num = nth_hexagonal_number(n);
        if (hex_num == -1) {
            printf("Invalid input or integer overflow occurred. Please enter a smaller positive integer.\n");
        } else {
            printf("The %" PRId64 "th hexagonal number is: %" PRId64 "\n", n, hex_num);
        }
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}