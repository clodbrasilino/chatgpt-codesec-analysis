#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int octal_to_decimal(const char *input, uintmax_t *result)
{
    char *end;
    uintmax_t value;

    if (input == NULL || result == NULL || input[0] == '\0' ||
        input[0] == '+' || input[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 8);

    if (errno == ERANGE || end == input || end == NULL || *end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
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
    uintmax_t decimal;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (octal_to_decimal(input, &decimal) != 0) {
        fputs("Invalid octal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}