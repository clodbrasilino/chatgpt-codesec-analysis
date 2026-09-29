#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 3U
#define INITIAL_CAPACITY 128U

static int is_valid_triangle(double a, double b, double c)
{
    double largest;
    double other1;
    double other2;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    largest = a;
    other1 = b;
    other2 = c;

    if (b > largest) {
        largest = b;
        other1 = a;
        other2 = c;
    }

    if (c > largest) {
        largest = c;
        other1 = a;
        other2 = b;
    }

    return largest - other1 < other2;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
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
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        ++length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    double sides[SIDE_COUNT];
    size_t i;

    if (read_line(stdin, &input) != 0) {
        fputs(ferror(stdin) ? "Input error\n" : "Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (i = 0U; i < SIDE_COUNT; ++i) {
        char *end;

        while (isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        if (*cursor == '\0') {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        sides[i] = strtod(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(sides[i])) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        cursor = end;
    }

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(sides[0], sides[1], sides[2])) {
        puts("Valid triangle");
    } else {
        puts("Invalid triangle");
    }

    free(input);
    return EXIT_SUCCESS;
}