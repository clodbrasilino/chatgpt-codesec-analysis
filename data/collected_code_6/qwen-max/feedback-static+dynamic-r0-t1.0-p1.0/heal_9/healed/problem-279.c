#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_decagonal_number(int64_t n) {
    if (n > 0 && n <= 46116860184273879 / 4 + 3/4) {
        int64_t result = 4 * n * n - 3 * n;
        return result;
    }
    return 0;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n > 46116860184273879 / 4 + 3/4) {
        fprintf(stderr, "Input too large for computation\n");
        return 1;
    }
    int64_t result = nth_decagonal_number(n);
    printf("The %" PRId64 "th decagonal number is: %" PRId64 "\n", n, result);
    return 0;
}