#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static void print_binary(unsigned long long value)
{
    char binary[sizeof(value) * CHAR_BIT + 1];
    char *position = binary + sizeof(binary);

    *--position = '\0';

    do {
        *--position = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0ULL);

    fputs(position, stdout);
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

    size_t length = 0;
    while (length < sizeof(input) && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof(input)) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    char *start = input;
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

    print_binary(value);
    return EXIT_SUCCESS;
}