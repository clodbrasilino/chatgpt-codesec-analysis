#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    const size_t required = sizeof value * CHAR_BIT + 1U;
    char temporary[sizeof value * CHAR_BIT];
    size_t length = 0U;

    if (buffer == NULL || size == 0U) {
        return 0;
    }

    do {
        temporary[length++] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL && length < sizeof temporary);

    if (size < length + 1U || size < required - (required - length - 1U)) {
        buffer[0] = '\0';
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        buffer[i] = temporary[length - i - 1U];
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    char input[128];
    char binary[sizeof(unsigned long long) * CHAR_BIT + 1U];
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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