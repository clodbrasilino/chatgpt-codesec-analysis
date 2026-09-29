#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || input[0] == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return false;
        }

        ++frequencies[digit];
    }

    return true;
}

int main(void)
{
    char input[47];
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= sizeof input) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}