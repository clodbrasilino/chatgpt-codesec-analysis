#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t result = 0;
    const unsigned char *p = (const unsigned char *)binary;

    if (binary == NULL || decimal == NULL) {
        return 0;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '\0') {
        return 0;
    }

    while (*p == '0' || *p == '1') {
        uint64_t bit = (uint64_t)(*p - '0');

        if (result > (UINT64_MAX - bit) / 2U) {
            return 0;
        }

        result = result * 2U + bit;
        ++p;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (*p != '\0') {
        return 0;
    }

    *decimal = result;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uint64_t decimal;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    if (binary_to_decimal(input, &decimal) == 0) {
        fputs("Invalid binary number\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        return 1;
    }

    if (fflush(stdout) == EOF) {
        return 1;
    }

    return 0;
}