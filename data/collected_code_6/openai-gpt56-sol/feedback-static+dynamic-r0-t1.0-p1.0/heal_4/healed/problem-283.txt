#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        size_t digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return 0;
        }

        digit = (size_t)(*p - (unsigned char)'0');

        if (++frequencies[digit] > digit) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0' && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}