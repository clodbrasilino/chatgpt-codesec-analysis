#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    size_t bits = 1;
    unsigned long long remaining = value;

    while (remaining > 1) {
        remaining >>= 1;
        ++bits;
    }

    if (buffer == NULL || size < bits + 1) {
        return 0;
    }

    buffer[bits] = '\0';

    do {
        buffer[--bits] = (char)('0' + (value & 1));
        value >>= 1;
    } while (value != 0);

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    char binary[sizeof(unsigned long long) * CHAR_BIT + 1];
    char *start;
    char *end;
    unsigned long long value;
    int ch;

    if (getline(&input, &capacity, stdin) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ch != EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (!decimal_to_binary(value, binary, sizeof binary)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%s\n", binary) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}