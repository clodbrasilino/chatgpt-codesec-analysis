#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1];
    size_t position = sizeof(binary);

    binary[--position] = '\0';

    do {
        if (position == 0) {
            return -1;
        }

        binary[--position] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0ULL);

    if (fputs(binary + position, stdout) == EOF) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(void)
{
    char input[256];
    char *start;
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    return print_binary(value) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}