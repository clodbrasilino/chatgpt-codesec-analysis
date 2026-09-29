#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static void print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1U];
    size_t index = sizeof(binary) - 1U;

    binary[index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    puts(&binary[index]);
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long value;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    print_binary(value);
    return EXIT_SUCCESS;
}