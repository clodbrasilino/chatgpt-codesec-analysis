#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_hex_even(const char *hex, int *is_even)
{
    size_t length;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*hex)) {
        ++hex;
    }

    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        hex += 2;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(hex);

    while (length > 0U && isspace((unsigned char)hex[length - 1U])) {
        --length;
    }

    if (length == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    switch (tolower((unsigned char)hex[length - 1U])) {
    case '0':
    case '2':
    case '4':
    case '6':
    case '8':
    case 'a':
    case 'c':
    case 'e':
        *is_even = 1;
        break;
    default:
        *is_even = 0;
        break;
    }

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    int even;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
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

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        size_t new_capacity;
        char *new_input;

        if (capacity == SIZE_MAX) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        new_capacity = capacity == 0U ? 1U : capacity + 1U;
        new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    if (!is_hex_even(input, &even)) {
        free(input);
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}