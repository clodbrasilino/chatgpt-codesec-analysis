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
        unsigned char character = data[i];

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
    bool *seen = calloc(seen_length, sizeof(*seen));
    if (seen == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        unsigned char input[BUFSIZ];
        size_t count = fread(input, sizeof(*input), sizeof(input), stdin);

        if (count > 0U) {
            unsigned char repeated = 0;
            int status = first_repeated_character(input, count, seen,
                                                  seen_length, &repeated);

            if (status > 0) {
                int output_status = printf("%c\n", (int)repeated);
                free(seen);
                return output_status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
            }

            if (status < 0) {
                break;
            }
        }

        if (count < sizeof(input)) {
            if (ferror(stdin)) {
                free(seen);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    int output_status = puts("No repeated character");
    free(seen);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}