#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    const size_t month_count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < month_count; ++i) {
        if (equal_ignore_case(month, months[i])) {
            return (int)i;
        }
    }

    return -1;
}

static bool read_line(char **line)
{
    enum { INITIAL_CAPACITY = 32 };

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        size_t available = capacity - length;

        if (fgets(buffer + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity >= (size_t)INT_MAX) {
            free(buffer);
            return false;
        }

        size_t new_capacity;

        if (capacity > (size_t)INT_MAX / 2) {
            new_capacity = (size_t)INT_MAX;
        } else {
            new_capacity = capacity * 2;
        }

        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return false;
        }

        buffer = new_buffer;
        capacity = new_capacity;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    *line = buffer;
    return true;
}

int main(void)
{
    char *month = NULL;

    if (!read_line(&month)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    int month_index = find_month(month);
    free(month);

    if (month_index < 0) {
        fputs("Invalid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    static const bool has_31_days[] = {
        true, false, true, false, true, false,
        true, true, false, true, false, true
    };

    puts(has_31_days[month_index] ? "Yes" : "No");
    return EXIT_SUCCESS;
}