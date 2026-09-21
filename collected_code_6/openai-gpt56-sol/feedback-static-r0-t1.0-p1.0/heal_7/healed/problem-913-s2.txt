#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0 &&
           isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    char *input = malloc((size_t)MAX_INPUT_LENGTH + 1);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 1, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    }

    size_t length = 0;
    while (length < MAX_INPUT_LENGTH &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == MAX_INPUT_LENGTH && input[length] != '\n') {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}