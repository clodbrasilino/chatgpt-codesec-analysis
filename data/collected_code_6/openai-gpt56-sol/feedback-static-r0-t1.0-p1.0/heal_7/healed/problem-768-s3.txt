#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

static int has_odd_parity(unsigned long long value)
{
    int parity = 0;

    while (value != 0ULL) {
        parity ^= 1;
        value &= value - 1ULL;
    }

    return parity;
}

int main(void)
{
    char input[256];
    char *end;
    unsigned long long value;
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(input, &end, 0);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}