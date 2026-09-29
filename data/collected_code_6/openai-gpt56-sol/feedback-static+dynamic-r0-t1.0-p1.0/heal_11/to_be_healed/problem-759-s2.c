#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096U

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0U;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == (unsigned char)'+' || *p == (unsigned char)'-') {
        ++p;
    }

    while (*p >= (unsigned char)'0' && *p <= (unsigned char)'9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0U || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }

    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }

    ++p;

    return *p == (unsigned char)'\0';
}

static bool discard_line_remainder(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n') {
            return true;
        }

        if (character == EOF) {
            return feof(stdin) != 0;
        }
    }
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length = 0U;
    int character;

    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    while (length + 1U < capacity) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n') {
            buffer[length] = '\0';
            return true;
        }

        if (character == EOF) {
            buffer[length] = '\0';
            return length > 0U && feof(stdin) != 0;
        }

        buffer[length++] = (char)character;
    }

    buffer[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = getchar();

    if (character == '\n') {
        return false;
    }

    if (character != EOF) {
        (void)discard_line_remainder();
    }

    return false;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(input, INPUT_SIZE)) {
        fputs("Input error\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}