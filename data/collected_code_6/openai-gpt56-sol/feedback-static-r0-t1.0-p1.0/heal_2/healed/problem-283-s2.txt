#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

int main(void)
{
    enum { INPUT_SIZE = 4096 };
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n' || input[length] == '\r') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    puts(frequencies_are_valid(input) ? "true" : "false");
    return EXIT_SUCCESS;
}