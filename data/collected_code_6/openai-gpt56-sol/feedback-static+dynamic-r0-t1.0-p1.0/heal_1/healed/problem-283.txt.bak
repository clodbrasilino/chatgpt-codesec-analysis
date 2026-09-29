#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const char *p = text; *p != '\0'; ++p) {
        unsigned int digit;

        if (*p < '0' || *p > '9') {
            return 0;
        }

        digit = (unsigned int)(*p - '0');

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
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");

    return EXIT_SUCCESS;
}