#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static bool first_and_last_equal(const char *str, size_t length)
{
    return str != NULL && length > 0 && str[0] == str[length - 1];
}

int main(void)
{
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 1);
    size_t length = 0;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(input + length,
                 (int)((size_t)MAX_INPUT_LENGTH - length + 1),
                 stdin) != NULL) {
        size_t i = length;

        while (input[i] != '\0' && input[i] != '\n') {
            ++i;
        }

        if (input[i] == '\n') {
            length = i;
            break;
        }

        length = i;

        if (length == (size_t)MAX_INPUT_LENGTH) {
            int character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                free(input);
                return EXIT_FAILURE;
            }

            if (character == EOF && ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }

            break;
        }
    }

    if (ferror(stdin) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(first_and_last_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}