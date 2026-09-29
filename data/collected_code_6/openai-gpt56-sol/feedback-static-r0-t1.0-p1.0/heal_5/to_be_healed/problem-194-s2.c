#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int octal_to_decimal(const char *input, uintmax_t *result)
{
    char *end;
    uintmax_t value;

    if (input == NULL || result == NULL || *input == '\0') {
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

static int read_line(FILE *stream, char **line)
{
    size_t length;
    size_t capacity;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    length = 0;
    capacity = 64;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    uintmax_t decimal;
    int status;

    input = NULL;
    status = read_line(stdin, &input);

    if (status < 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("No input provided\n", stderr);
        return EXIT_FAILURE;
    }

    if (octal_to_decimal(input, &decimal) != 0) {
        free(input);
        fputs("Invalid octal number\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}