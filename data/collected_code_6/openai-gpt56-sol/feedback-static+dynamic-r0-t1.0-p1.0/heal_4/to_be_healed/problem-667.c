#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_vowels(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        int ch = tolower((unsigned char)*str);

        if (ch == 'a' || ch == 'e' || ch == 'i' ||
            ch == 'o' || ch == 'u') {
            ++count;
        }

        ++str;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (capacity - length < 2) {
            size_t required = length + 2;
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = length + 1;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_vowels(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fflush(stdout) == EOF || ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}