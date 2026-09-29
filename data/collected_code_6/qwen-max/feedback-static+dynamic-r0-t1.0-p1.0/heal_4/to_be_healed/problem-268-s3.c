#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_star_number(int64_t n) {
    int64_t max_n = 9223372036854775807 / 6 + 1;
    if (n > 0 && n < max_n) {
        int64_t result;
        __builtin_mul_overflow(n, n - 1, &result);
        __builtin_mul_overflow(result, 6, &result);
        return result + 1;
    } else {
        return -1;
    }
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int64_t result = nth_star_number(n);
    if (result == -1) {
        printf("Input too large to compute.\n");
        return 1;
    }
    printf("The %" PRId64 "th star number is: %" PRId64 "\n", n, result);
    return 0;
}