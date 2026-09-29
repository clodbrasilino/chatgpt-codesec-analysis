#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MONTH_CAPACITY = 32 };

static bool equals_ignore_case(const char *left, const char *right)
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

static bool month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    if (month == NULL) {
        return false;
    }

    for (size_t i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_line(FILE *stream)
{
    if (stream == NULL) {
        return false;
    }

    int ch;

    while ((ch = fgetc(stream)) != '\n') {
        if (ch == EOF) {
            return feof(stream) != 0;
        }
    }

    return true;
}

static bool read_line(FILE *stream, char *buffer, size_t capacity)
{
    if (stream == NULL || buffer == NULL || capacity < 2 ||
        capacity > (size_t)INT_MAX) {
        return false;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return false;
    }

    char *newline = memchr(buffer, '\n', capacity);

    if (newline != NULL) {
        if (newline > buffer && newline[-1] == '\r') {
            newline[-1] = '\0';
        } else {
            *newline = '\0';
        }

        return true;
    }

    char *terminator = memchr(buffer, '\0', capacity);

    if (terminator == NULL) {
        buffer[0] = '\0';
        return false;
    }

    if (terminator > buffer && terminator[-1] == '\r') {
        terminator[-1] = '\0';
        return true;
    }

    if (feof(stream)) {
        return true;
    }

    if (!discard_line(stream)) {
        buffer[0] = '\0';
        return false;
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char *month = malloc(MONTH_CAPACITY);

    if (month == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, month, MONTH_CAPACITY)) {
        fputs("Failed to read a valid month name.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}