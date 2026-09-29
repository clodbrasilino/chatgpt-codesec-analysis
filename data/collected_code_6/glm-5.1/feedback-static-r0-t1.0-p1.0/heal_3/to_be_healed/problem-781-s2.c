#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char* check_divisor_count_parity(long long n) {
    if (n <= 0) {
        return "invalid";
    }
    long long root = (long long)sqrt((double)n);
    if (root * root == n) {
        return "odd";
    }
    return "even";
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Error: Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    const char *result = check_divisor_count_parity(val);
    printf("%s\n", result);

    return EXIT_SUCCESS;
}