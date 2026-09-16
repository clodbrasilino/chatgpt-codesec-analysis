#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return false;
    }

    for (const char *p = input; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') {
            return false;
        }

        unsigned int digit = (unsigned int)(*p - '0');
        ++frequencies[digit];

        if (frequencies[digit] > digit) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    } else if (!feof(stdin)) {
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            fputs("Input too long\n", stderr);
            return EXIT_FAILURE;
        }
        if (ch == EOF && ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}