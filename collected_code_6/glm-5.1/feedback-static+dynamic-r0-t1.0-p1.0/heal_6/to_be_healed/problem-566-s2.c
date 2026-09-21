#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int get_sum(unsigned int n) {
    unsigned int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned int result = get_sum(n);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}