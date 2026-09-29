#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6666666666 * 2222222221 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:856,execs:390,op:havoc,rep:3)
     */
    int64_t result = 3 * n * (n - 1) + 1;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
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