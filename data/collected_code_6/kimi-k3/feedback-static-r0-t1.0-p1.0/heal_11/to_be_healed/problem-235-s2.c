#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

uint32_t set_even_bits(uint32_t num)
{
    return num | 0xAAAAAAAAU;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long value;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'overflow' can be reduced. [variableScope]
     */
    int overflow = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer) && buffer[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            overflow = 1;
        }
        if (overflow || c == EOF) {
            return 1;
        }
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (endptr == buffer || errno == ERANGE || value > UINT32_MAX) {
        return 1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 1;
    }

    printf("%" PRIu32 "\n", set_even_bits((uint32_t)value));

    return 0;
}