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
    bool seen[UCHAR_MAX + 1] = { false };
    unsigned char repeated = 0;
    int found = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (!found && seen[value]) {
            repeated = value;
            found = 1;
        }

        seen[value] = true;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (found) {
        if (printf("%c\n", repeated) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}