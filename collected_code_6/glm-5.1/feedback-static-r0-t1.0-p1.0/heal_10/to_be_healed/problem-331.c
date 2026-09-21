#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    int bits = sizeof(n) * CHAR_BIT;
    for (int i = 0; i < bits; i++) {
        count += !(n & 1);
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
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int unset_bits = count_unset_bits(num);
    printf("%d\n", unset_bits);
    return EXIT_SUCCESS;
}