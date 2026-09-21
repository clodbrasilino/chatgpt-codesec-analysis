#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long centered_hexagonal(unsigned int n) {
    unsigned long long term = n;
    return 3 * term * (term - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0 || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "%llu\n", centered_hexagonal(n));
    if (len < 0 || (unsigned int)len >= sizeof(buf)) {
        return EXIT_FAILURE;
    }
    fputs(buf, stdout);

    return EXIT_SUCCESS;
}