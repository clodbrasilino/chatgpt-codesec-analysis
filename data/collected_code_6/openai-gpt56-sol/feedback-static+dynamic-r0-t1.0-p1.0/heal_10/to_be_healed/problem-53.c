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
    bool complete = false;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        size_t remaining = (size_t)MAX_INPUT_LENGTH - length;
        int chunk_size = remaining >= (size_t)BUFSIZ
                       ? BUFSIZ
                       : (int)(remaining + 1);

        if (fgets(input + length, chunk_size, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            complete = true;
            break;
        }

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
            complete = true;
            break;
        }
    }

    if (!complete && length == (size_t)MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char extra[2];

        if (fgets(extra, sizeof extra, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
        } else if (extra[0] != '\n') {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(first_and_last_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}