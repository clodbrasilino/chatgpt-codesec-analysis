#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

int count_set_bits(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) > 10) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    uint32_t num = (uint32_t)val;
    int result = count_set_bits(num);
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}