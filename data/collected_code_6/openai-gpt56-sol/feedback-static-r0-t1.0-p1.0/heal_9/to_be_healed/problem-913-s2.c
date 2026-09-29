#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0 &&
           isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2);
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

        input[0] = '\0';
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        fputs("Input is too large.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    } else if (length == MAX_INPUT_LENGTH && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char extra[2];

        if (fgets(extra, sizeof extra, stdin) == NULL) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
        } else if (extra[0] != '\n') {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}