#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    char temporary[sizeof(value) * CHAR_BIT];
    size_t length = 0;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    do {
        temporary[length++] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    if (length >= size) {
        buffer[0] = '\0';
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        buffer[i] = temporary[length - i - 1];
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    enum {
        INPUT_SIZE = 128,
        BINARY_SIZE = sizeof(unsigned long long) * CHAR_BIT + 1
    };

    char input[INPUT_SIZE];
    char binary[BINARY_SIZE];
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
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