#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

static bool contains_only_allowed_characters(const char *string)
{
    const unsigned char *p;

    if (string == NULL || *string == '\0') {
        return false;
    }

    for (p = (const unsigned char *)string; *p != '\0'; ++p) {
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
    char input[MAX_INPUT_LENGTH + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        puts("invalid");
        return EXIT_SUCCESS;
    }

    size_t length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");
    return EXIT_SUCCESS;
}