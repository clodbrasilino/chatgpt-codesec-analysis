#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int toggle_odd_bits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 0);

    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int result = toggle_odd_bits((unsigned int)val);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}