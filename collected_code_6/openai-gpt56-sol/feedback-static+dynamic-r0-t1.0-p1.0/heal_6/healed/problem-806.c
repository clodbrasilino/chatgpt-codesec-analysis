#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(const char *str)
{
    size_t max_run = 0;
    size_t current_run = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            ++current_run;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
        ++str;
    }

    return max_run;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1048576 };
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    size_t length = 0;
    int ch = EOF;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= (size_t)MAX_INPUT_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    if (printf("%zu\n", max_uppercase_run(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}