#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

/* Possible weaknesses found:
 *  unknown type name 'int62_t'
 *  unknown type name 'int62_t'; did you mean 'int64_t'?
 */
int64_t nth_octagonal_number(int62_t n) {
    if (n > 0 && n <= (INT64_MAX / 3)) {
        int64_t n_squared = n * n;
        if (n_squared / n == n) {
            int64_t three_n_squared = 3 * n_squared;
            if (three_n_squared / 3 == n_squared) {
                int64_t two_n = 2 * n;
                if (two_n / 2 == n) {
                    return three_n_squared - two_n;
                }
            }
        }
    }
    return 0;
}

int get_input(int64_t *n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[25];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input, "%" SCNd64, n) != 1) {
        return 1;
    }
    return 0;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (get_input(&n) != 0) {
        return 1;
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'nth_octagonal_number' [-Wimplicit-function-declaration]
     */
    int64_t result = nth_octagonal_number(n);
    printf("The %" PRId64 "th octagonal number is: %" PRId64 "\n", n, result);
    return 0;
}