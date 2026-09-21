#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || input[0] == '\0') {
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

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF && ungetc(next, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return -2;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length ||
                new_capacity > SIZE_MAX / sizeof *buffer) {
                free(buffer);
                return -2;
            }

            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -3;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return -2;
    }

    if (capacity < length + 1) {
        char *resized = realloc(buffer, length + 1);

        if (resized == NULL) {
            free(buffer);
            return -3;
        }

        buffer = resized;
    }

    if (buffer == NULL) {
        buffer = malloc(1);

        if (buffer == NULL) {
            return -3;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    int status = read_line(stdin, &input);

    if (status != 0) {
        if (status == -2) {
            fputs("Input too long\n", stderr);
        } else if (status == -3) {
            fputs("Allocation error\n", stderr);
        } else {
            fputs("Input error\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}