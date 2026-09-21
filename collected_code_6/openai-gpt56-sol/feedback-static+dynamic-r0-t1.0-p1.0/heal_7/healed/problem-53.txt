#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static bool first_and_last_equal(const char *str, size_t length)
{
    return str != NULL && length > 0 && str[0] == str[length - 1];
}

int main(void)
{
    char *input = malloc(MAX_INPUT_LENGTH);
    size_t length = 0;
    int character;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = getchar()) != EOF && character != '\n') {
        if (length >= MAX_INPUT_LENGTH) {
            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(first_and_last_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}