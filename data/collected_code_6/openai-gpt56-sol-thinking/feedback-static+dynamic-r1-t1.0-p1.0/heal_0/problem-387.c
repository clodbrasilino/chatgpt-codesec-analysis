#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int hex_is_even(const char *input, bool *is_even)
{
    const unsigned char *p;
    unsigned int last_digit = 0;
    size_t digit_count = 0;

    if (input == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)input;

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    } else if (*p == '-') {
        return 0;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (isxdigit(*p)) {
        if (*p >= '0' && *p <= '9') {
            last_digit = (unsigned int)(*p - '0');
        } else {
            last_digit = (unsigned int)(tolower(*p) - 'a' + 10);
        }

        ++digit_count;
        ++p;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (digit_count == 0 || *p != '\0') {
        return 0;
    }

    *is_even = (last_digit % 2U) == 0U;
    return 1;
}

int main(void)
{
    char input[256];
    bool is_even;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (ch = 0; input[ch] != '\0' && input[ch] != '\n'; ++ch) {
    }

    if (input[ch] == '\0') {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (!hex_is_even(input, &is_even)) {
        return EXIT_FAILURE;
    }

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}