#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int find_parity(uint32_t num) {
    int parity = 0;
    while (num) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return parity;
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

    uint32_t num = (uint32_t)val;
    int parity = find_parity(num);

    printf("%d\n", parity);

    return EXIT_SUCCESS;
}