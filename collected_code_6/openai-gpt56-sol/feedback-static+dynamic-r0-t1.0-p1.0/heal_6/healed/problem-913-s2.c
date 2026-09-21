#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0U;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return true;
            }
            ++i;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        puts("false");
        free(input);
        return EXIT_SUCCESS;
    }

    size_t length = 0U;
    while (length < (size_t)MAX_INPUT_LENGTH + 1U &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (!discard_remaining_input()) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}