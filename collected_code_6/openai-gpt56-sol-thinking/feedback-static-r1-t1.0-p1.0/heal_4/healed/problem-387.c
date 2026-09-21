#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 256U
#define MAX_LINE_LENGTH (1024U * 1024U)

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    const size_t maximum_capacity = (size_t)MAX_LINE_LENGTH + 1U;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\0' || length >= (size_t)MAX_LINE_LENGTH) {
            free(buffer);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= maximum_capacity) {
                free(buffer);
                return 0;
            }

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = capacity * 2U;
                if (new_capacity > maximum_capacity) {
                    new_capacity = maximum_capacity;
                }
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 1;
}

static int hex_is_even(const char *input, bool *is_even)
{
    const unsigned char *p;
    unsigned int last_digit = 0U;
    size_t digit_count = 0U;

    if (input == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)input;

    while (*p != '\0' && isspace((int)*p) != 0) {
        ++p;
    }

    if (*p == (unsigned char)'+') {
        ++p;
    } else if (*p == (unsigned char)'-') {
        return 0;
    }

    if (p[0] == (unsigned char)'0' &&
        (p[1] == (unsigned char)'x' || p[1] == (unsigned char)'X')) {
        p += 2;
    }

    while (*p != '\0' && isxdigit((int)*p) != 0) {
        if (*p >= (unsigned char)'0' && *p <= (unsigned char)'9') {
            last_digit = (unsigned int)(*p - (unsigned char)'0');
        } else {
            last_digit = (unsigned int)(
                tolower((int)*p) - (int)'a' + 10
            );
        }

        ++digit_count;
        ++p;
    }

    while (*p != '\0' && isspace((int)*p) != 0) {
        ++p;
    }

    if (digit_count == 0U || *p != '\0') {
        return 0;
    }

    *is_even = (last_digit & 1U) == 0U;
    return 1;
}

int main(void)
{
    char *input = NULL;
    bool is_even = false;

    if (read_line(stdin, &input) == 0) {
        return EXIT_FAILURE;
    }

    if (hex_is_even(input, &is_even) == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}