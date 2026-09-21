#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum { INPUT_SIZE = 1024 };

static int is_hex_digit(unsigned char character)
{
    return (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'f') ||
           (character >= (unsigned char)'A' &&
            character <= (unsigned char)'F');
}

static int is_hexadecimal(const char *text, size_t length)
{
    size_t index = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    if (length >= 2 &&
        text[0] == '0' &&
        (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
    }

    if (index == length) {
        return 0;
    }

    for (; index < length; ++index) {
        if (!is_hex_digit((unsigned char)text[index])) {
            return 0;
        }
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)text[length - 1];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((unsigned int)(digit - (unsigned char)'0') % 2U) == 0U;
    }

    if (digit >= (unsigned char)'A' && digit <= (unsigned char)'F') {
        digit = (unsigned char)(digit - (unsigned char)'A' +
                                (unsigned char)'a');
    }

    if (digit >= (unsigned char)'a' && digit <= (unsigned char)'f') {
        return ((unsigned int)(digit - (unsigned char)'a') + 10U) % 2U == 0U;
    }

    return 0;
}

static int discard_remaining_input(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t length = 0;
    int line_complete = 0;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Input error\n" : "No input\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length > 0 && input[length - 1] == '\n') {
        line_complete = 1;
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    }

    if (!line_complete && !feof(stdin)) {
        if (discard_remaining_input() != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");
    return EXIT_SUCCESS;
}