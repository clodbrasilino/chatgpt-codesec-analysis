#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const char *string,
                                    size_t length,
                                    unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

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
    bool found = false;
    unsigned char repeated = 0;
    unsigned char input[4096];

    while (!found) {
        size_t count = fread(input, 1, sizeof input, stdin);

        for (size_t i = 0; i < count; ++i) {
            if (input[i] == '\n') {
                found = true;
                break;
            }

            if (seen[input[i]]) {
                repeated = input[i];

                if (printf("%c\n", repeated) < 0) {
                    return EXIT_FAILURE;
                }

                return EXIT_SUCCESS;
            }

            seen[input[i]] = true;
        }

        if (count < sizeof input) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (printf("No repeated character\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}