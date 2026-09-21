#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static void print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1];
    size_t index = sizeof(binary);

    binary[--index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    fputs(binary + index, stdout);
    fputc('\n', stdout);
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

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
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