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
    size_t frequencies[10] = {0};
    int has_input = 0;
    int valid = 1;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        size_t digit;

        has_input = 1;

        if (ch < '0' || ch > '9') {
            valid = 0;
            continue;
        }

        digit = (size_t)(ch - '0');

        if (++frequencies[digit] > digit) {
            valid = 0;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (!has_input) {
        valid = 0;
    }

    puts(valid ? "true" : "false");
    return EXIT_SUCCESS;
}