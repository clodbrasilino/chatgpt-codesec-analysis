#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_hex_even(const char *hex, int *is_even)
{
    const unsigned char *p;
    int last_digit = -1;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)hex;

    while (isspace(*p)) {
        ++p;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (isxdigit(*p)) {
        last_digit = *p;
        ++p;
    }

    if (last_digit < 0) {
        return 0;
    }

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (*p != '\0') {
        return 0;
    }

    *is_even = last_digit == '0' || last_digit == '2' ||
               last_digit == '4' || last_digit == '6' ||
               last_digit == '8' || last_digit == 'a' ||
               last_digit == 'A' || last_digit == 'c' ||
               last_digit == 'C' || last_digit == 'e' ||
               last_digit == 'E';

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int even;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
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

    if (length + 1 >= capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
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