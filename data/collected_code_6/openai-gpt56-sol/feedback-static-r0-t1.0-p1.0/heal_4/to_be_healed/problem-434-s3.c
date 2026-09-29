#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Input error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}