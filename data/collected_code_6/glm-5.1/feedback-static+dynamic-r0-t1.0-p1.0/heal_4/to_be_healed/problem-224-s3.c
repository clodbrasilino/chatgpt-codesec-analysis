#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int count_set_bits(unsigned int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX || (val == ULONG_MAX && errno == ERANGE) || errno == ERANGE) {
        fprintf(stderr, "Error: Invalid input. Must be a valid unsigned integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    unsigned int result = count_set_bits(num);

    printf("%u\n", result);
    fflush(stdout);
    return EXIT_SUCCESS;
}