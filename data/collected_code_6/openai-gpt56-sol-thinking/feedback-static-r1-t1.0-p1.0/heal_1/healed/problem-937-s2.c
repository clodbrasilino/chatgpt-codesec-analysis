#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool count_most_common_character(const char *string,
                                 unsigned char *character,
                                 size_t *count)
{
    size_t frequencies[(size_t)UCHAR_MAX + 1U] = {0};
    const unsigned char *current;
    size_t highest = 0;
    unsigned char most_common = 0;

    if (string == NULL || character == NULL || count == NULL ||
        *string == '\0') {
        return false;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        ++frequencies[*current];
        ++current;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (frequencies[*current] > highest) {
            highest = frequencies[*current];
            most_common = *current;
        }

        ++current;
    }

    *character = most_common;
    *count = highest;

    return true;
}

int main(int argc, char * const argv[])
{
    unsigned char character;
    size_t count;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!count_most_common_character(argv[1], &character, &count)) {
        if (fputs("The string must not be empty.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("Most common character: %c\nCount: %zu\n",
               character,
               count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}