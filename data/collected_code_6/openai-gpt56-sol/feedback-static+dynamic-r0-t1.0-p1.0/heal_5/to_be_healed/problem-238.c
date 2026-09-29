#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t a;
    uintmax_t b;

    if (count == NULL) {
        return 0;
    }

#if SIZE_MAX > UINTMAX_MAX
    if (length > UINTMAX_MAX) {
        return 0;
    }
#endif

    a = (uintmax_t)length;

    if (a == UINTMAX_MAX) {
        return 0;
    }

    b = a + UINTMAX_C(1);

    if ((a & UINTMAX_C(1)) == 0) {
        a /= UINTMAX_C(2);
    } else {
        b /= UINTMAX_C(2);
    }

    if (a != 0 && b > UINTMAX_MAX / a) {
        return 0;
    }

    *count = a * b;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;

    if (stream == NULL || line == NULL || length == NULL) {
        return 0;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
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
            if (ferror(stream) || used == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (used == capacity) {
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

        buffer[used] = (char)(unsigned char)ch;
        ++used;
    }

    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    uintmax_t count;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

    if (!count_nonempty_substrings(length, &count)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}