#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    size_t bits = 1U;
    unsigned long long remaining = value;

    while (remaining > 1ULL) {
        remaining >>= 1U;
        ++bits;
    }

    if (buffer == NULL || size <= bits) {
        return 0;
    }

    buffer[bits] = '\0';

    do {
        buffer[--bits] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(unsigned long long) * CHAR_BIT + 1U];
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(end, &end, 10);

    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (!decimal_to_binary(value, binary, sizeof binary)) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", binary) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}