#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (++frequencies[digit] > digit) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input too long\n", stderr);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation error\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            fputs("Memory allocation error\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    puts(has_valid_digit_frequencies(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}