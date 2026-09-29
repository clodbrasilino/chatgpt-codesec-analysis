#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_hexagonal_number(int64_t n) {
    if (n < 1 || n > 3037000499) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1163,execs:390,op:havoc,rep:5)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[21];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (sscanf(input, "%" SCNd64, &n) == 1 && n > 0) {
            int64_t hex_num = nth_hexagonal_number(n);
            if (hex_num == -1) {
                printf("Invalid input or integer overflow occurred. Please enter a smaller positive integer.\n");
            } else {
                printf("The %" PRId64 "th hexagonal number is: %" PRId64 "\n", n, hex_num);
            }
        } else {
            printf("Invalid input. Please enter a positive integer.\n");
        }
    } else {
        printf("Input error. Please try again.\n");
    }
    return 0;
}