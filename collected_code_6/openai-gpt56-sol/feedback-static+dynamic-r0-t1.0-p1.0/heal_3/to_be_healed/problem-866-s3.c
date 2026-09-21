#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (line == NULL) {
        return false;
    }

    *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity <= capacity) {
                free(*line);
                *line = NULL;
                return false;
            }

            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                return false;
            }

            *line = new_line;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(*line);
        *line = NULL;
        return false;
    }

    if (character == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return false;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(*line);
            *line = NULL;
            return false;
        }

        char *new_line = realloc(*line, capacity + 1);
        if (new_line == NULL) {
            free(*line);
            *line = NULL;
            return false;
        }

        *line = new_line;
    }

    (*line)[length] = '\0';
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