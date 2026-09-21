#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

static bool contains_only_allowed_characters(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string; *p != '\0'; ++p) {
        if (!((*p >= 'A' && *p <= 'Z') ||
              (*p >= 'a' && *p <= 'z') ||
              (*p >= '0' && *p <= '9'))) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1];
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");

    return EXIT_SUCCESS;
}