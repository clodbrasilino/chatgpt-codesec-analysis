#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool find_max_occurring_character(const char *string, unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *cursor;
    size_t maximum = 0;

    if (string == NULL || result == NULL || string[0] == '\0') {
        return false;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        ++frequencies[*cursor];
        if (frequencies[*cursor] > maximum) {
            maximum = frequencies[*cursor];
        }
        ++cursor;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        if (frequencies[*cursor] == maximum) {
            *result = *cursor;
            return true;
        }
        ++cursor;
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    unsigned char result;
    size_t length;
    int character;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read a string.\n", stderr);
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
        if (length > 0 && input[length - 1] == '\r') {
            input[length - 1] = '\0';
        }
    } else if (!feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            fputs("Failed while reading the string.\n", stderr);
        } else {
            fputs("Input string is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, &result)) {
        fputs("The string must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}