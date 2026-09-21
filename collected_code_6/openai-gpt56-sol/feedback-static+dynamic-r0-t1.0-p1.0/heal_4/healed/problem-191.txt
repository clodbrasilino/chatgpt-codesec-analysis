#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stream);
}

static bool read_line(FILE *stream, char *buffer, size_t capacity)
{
    if (stream == NULL || buffer == NULL || capacity < 2 ||
        capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return false;
    }

    size_t length = 0;

    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (buffer[length] == '\r') {
        buffer[length] = '\0';

        int ch = fgetc(stream);

        if (ch != '\n' && ch != EOF && ungetc(ch, stream) == EOF) {
            return false;
        }

        return true;
    }

    if (feof(stream)) {
        return true;
    }

    if (!discard_line(stream)) {
        return false;
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char *month = malloc(MONTH_CAPACITY);

    if (month == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, month, MONTH_CAPACITY)) {
        fprintf(stderr, "Failed to read a valid month name.\n");
        free(month);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}