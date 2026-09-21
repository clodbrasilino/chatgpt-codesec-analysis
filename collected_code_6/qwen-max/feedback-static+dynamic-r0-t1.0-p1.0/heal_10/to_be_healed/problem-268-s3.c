#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_star_number(int64_t n) {
    int64_t max_n = 9223372036854775807 / 6 + 1;
    if (n > 0 && n < max_n) {
        int64_t result;
        if (__builtin_mul_overflow(n, n - 1, &result) || __builtin_mul_overflow(result, 6, &result)) {
            return -1;
        }
        return result + 1;
    } else {
        return -1;
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[25];
    fgets(input, sizeof(input), stdin);
    int64_t n;
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input, "%" SCNd64, &n) != 1) {
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