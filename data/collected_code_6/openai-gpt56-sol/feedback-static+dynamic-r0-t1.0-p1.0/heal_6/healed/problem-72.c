#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

static bool is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static bool read_int64(int64_t *result)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    intmax_t value;
    int ch;

    if (result == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(line);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return false;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return false;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(line);
        return false;
    }

    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            return false;
        }
    }

    line[length] = '\0';

    errno = 0;
    value = strtoimax(line, &end, 10);

    if (end == line || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        free(line);
        return false;
    }

    while (*end != '\0' && is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (!is_space_character((unsigned char)ch)) {
            free(line);
            return false;
        }
    }

    if (ferror(stdin)) {
        free(line);
        return false;
    }

    *result = (int64_t)value;
    free(line);
    return true;
}

int main(void)
{
    int64_t value;

    if (!read_int64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}