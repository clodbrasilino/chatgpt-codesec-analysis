#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)input;
         *p != '\0';
         ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return false;
        }

        ++frequencies[digit];
    }

    return true;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (ch == EOF && length == 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}