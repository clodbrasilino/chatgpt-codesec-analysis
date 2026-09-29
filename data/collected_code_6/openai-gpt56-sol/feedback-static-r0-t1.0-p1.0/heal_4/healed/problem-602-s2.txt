#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const unsigned char *data,
                                    size_t length,
                                    bool seen[static UCHAR_MAX + 1],
                                    unsigned char *result)
{
    if (data == NULL || seen == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char character = data[i];

        if (character == '\n') {
            return -1;
        }

        if (seen[character]) {
            *result = character;
            return 1;
        }

        seen[character] = true;
    }

    return 0;
}

int main(void)
{
    bool seen[UCHAR_MAX + 1] = { false };
    unsigned char input[BUFSIZ];

    for (;;) {
        const size_t count = fread(input, sizeof input[0], sizeof input, stdin);

        if (count != 0U) {
            unsigned char repeated;
            const int status =
                first_repeated_character(input, count, seen, &repeated);

            if (status > 0) {
                return printf("%c\n", (int)repeated) < 0
                           ? EXIT_FAILURE
                           : EXIT_SUCCESS;
            }

            if (status < 0) {
                break;
            }
        }

        if (count < sizeof input) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }
    }

    return puts("No repeated character") == EOF
               ? EXIT_FAILURE
               : EXIT_SUCCESS;
}