#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const unsigned char *data,
                                    size_t length,
                                    bool *seen,
                                    size_t seen_length,
                                    unsigned char *result)
{
    if (data == NULL || seen == NULL || result == NULL ||
        seen_length < (size_t)UCHAR_MAX + 1U) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char character = data[i];

        if (character == '\n') {
            return -1;
        }

        if (seen[(size_t)character]) {
            *result = character;
            return 1;
        }

        seen[(size_t)character] = true;
    }

    return 0;
}

int main(void)
{
    const size_t seen_length = (size_t)UCHAR_MAX + 1U;
    bool *seen = calloc(seen_length, sizeof *seen);
    unsigned char *input = malloc(BUFSIZ);

    if (seen == NULL || input == NULL) {
        free(input);
        free(seen);
        return EXIT_FAILURE;
    }

    int exit_status = EXIT_SUCCESS;
    bool finished = false;

    while (!finished) {
        const size_t count = fread(input, sizeof *input, BUFSIZ, stdin);

        if (count > 0U) {
            unsigned char repeated = 0;
            const int status = first_repeated_character(
                input, count, seen, seen_length, &repeated);

            if (status > 0) {
                if (printf("%c\n", (int)repeated) < 0) {
                    exit_status = EXIT_FAILURE;
                }
                finished = true;
                continue;
            }

            if (status < 0) {
                if (puts("No repeated character") == EOF) {
                    exit_status = EXIT_FAILURE;
                }
                finished = true;
                continue;
            }
        }

        if (count < BUFSIZ) {
            if (ferror(stdin)) {
                exit_status = EXIT_FAILURE;
            } else if (puts("No repeated character") == EOF) {
                exit_status = EXIT_FAILURE;
            }
            finished = true;
        }
    }

    free(input);
    free(seen);
    return exit_status;
}