#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_hex_even(const char *hex, int *is_even)
{
    const unsigned char *p;
    unsigned char last_digit = 0;
    int has_digit = 0;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)hex;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (*p != '\0' && isxdigit(*p)) {
        last_digit = *p++;
        has_digit = 1;
    }

    if (!has_digit) {
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

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int character;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return 0;
            }
            break;
        }

        buffer[length++] = (char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    int even;

    if (!read_line(stdin, &input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_hex_even(input, &even)) {
        free(input);
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    free(input);
    return EXIT_SUCCESS;
}