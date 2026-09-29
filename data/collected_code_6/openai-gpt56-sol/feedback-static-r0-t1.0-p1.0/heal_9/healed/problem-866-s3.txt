#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_LINE_LENGTH = 4096
};

static bool equal_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int find_month(const char *month)
{
    static const char *const months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if (month == NULL) {
        return -1;
    }

    size_t month_count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < month_count; ++i) {
        if (equal_ignore_case(month, months[i])) {
            return (int)i;
        }
    }

    return -1;
}

static bool month_has_31_days(int month_index)
{
    static const bool has_31_days[] = {
        true, false, true, false,
        true, false, true, true,
        false, true, false, true
    };

    size_t month_count = sizeof has_31_days / sizeof has_31_days[0];

    return month_index >= 0 &&
           (size_t)month_index < month_count &&
           has_31_days[(size_t)month_index];
}

static bool discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ch == '\n' || (feof(stream) && !ferror(stream));
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }

            if (next == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length >= MAX_LINE_LENGTH) {
            if (!discard_line(stream)) {
                free(buffer);
                return NULL;
            }

            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity > (size_t)MAX_LINE_LENGTH + 1) {
                new_capacity = (size_t)MAX_LINE_LENGTH + 1;
            }

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

    char *result = realloc(buffer, length + 1);
    return result != NULL ? result : buffer;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    int month_index = find_month(month);
    free(month);

    if (month_index < 0) {
        fputs("Invalid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month_index) ? "Yes" : "No");
    return EXIT_SUCCESS;
}