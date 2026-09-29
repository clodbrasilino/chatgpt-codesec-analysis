#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0U &&
           isdigit((unsigned char)str[length - 1U]) != 0;
}

static bool discard_remaining_input(void)
{
    char buffer[256];

    while (fgets(buffer, (int)sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return true;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 2U];

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        puts("false");
        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (discard_remaining_input()) {
            fputs("Input is too large.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(ends_with_number(input, length) ? "true" : "false");
    return EXIT_SUCCESS;
}