#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 16,
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

    const size_t month_count = sizeof months / sizeof months[0];

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

    const size_t month_count = sizeof has_31_days / sizeof has_31_days[0];

    return month_index >= 0 &&
           (size_t)month_index < month_count &&
           has_31_days[(size_t)month_index];
}

static bool consume_line_remainder(FILE *stream)
{
    unsigned char buffer[256];

    if (stream == NULL) {
        return false;
    }

    for (;;) {
        size_t count = fread(buffer, 1, sizeof buffer, stream);

        for (size_t i = 0; i < count; ++i) {
            if (buffer[i] == '\n') {
                long unread = (long)(count - i - 1);

                if (unread > 0 && fseek(stream, -unread, SEEK_CUR) != 0) {
                    return false;
                }

                return true;
            }
        }

        if (count < sizeof buffer) {
            return feof(stream) && !ferror(stream);
        }
    }
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    char *buffer = malloc((size_t)MAX_LINE_LENGTH + 1);

    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, MAX_LINE_LENGTH + 1, stream) == NULL) {
        free(buffer);
        return NULL;
    }

    size_t length = 0;

    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\r') {
        if (buffer[length + 1] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        buffer[length] = '\0';
        return buffer;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return buffer;
    }

    if (length == MAX_LINE_LENGTH) {
        int next = fgetc(stream);

        if (next == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        if (next == '\r') {
            int after_cr = fgetc(stream);

            if (after_cr != '\n' && after_cr != EOF &&
                ungetc(after_cr, stream) == EOF) {
                free(buffer);
                return NULL;
            }

            if (after_cr == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            buffer[length] = '\0';
            return buffer;
        }

        if (next != EOF) {
            if (!consume_line_remainder(stream)) {
                free(buffer);
                return NULL;
            }

            free(buffer);
            return NULL;
        }

        if (ferror(stream)) {
            free(buffer);
            return NULL;
        }
    }

    return buffer;
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