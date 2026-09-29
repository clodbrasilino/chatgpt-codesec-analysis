#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const char *p = text; *p != '\0'; ++p) {
        size_t digit;

        if (*p < '0' || *p > '9') {
            return 0;
        }

        digit = (size_t)(*p - '0');

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

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}