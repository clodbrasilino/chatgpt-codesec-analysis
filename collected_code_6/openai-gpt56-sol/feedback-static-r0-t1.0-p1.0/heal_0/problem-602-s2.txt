#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const char *string, unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || result == NULL) {
        return 0;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (seen[character]) {
            *result = character;
            return 1;
        }

        seen[character] = true;
        ++string;
    }

    return 0;
}

int main(void)
{
    char input[1024];
    unsigned char repeated;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (first_repeated_character(input, &repeated)) {
        if (printf("%c\n", repeated) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated character\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}