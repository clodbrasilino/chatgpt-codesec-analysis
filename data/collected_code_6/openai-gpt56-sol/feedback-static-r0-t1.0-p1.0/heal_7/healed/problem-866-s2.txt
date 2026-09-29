#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 128

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

static bool month_has_31_days(const char *month)
{
    static const char *const months[] = {
        "January",
        "March",
        "May",
        "July",
        "August",
        "October",
        "December"
    };

    const size_t count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char *buffer, size_t size)
{
    if (stream == NULL || buffer == NULL || size < 2) {
        return false;
    }

    if (fgets(buffer, (int)size, stream) == NULL) {
        return false;
    }

    size_t length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';

        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (!feof(stream)) {
        int character;

        do {
            character = fgetc(stream);
        } while (character != '\n' && character != EOF);

        return false;
    }

    return true;
}

int main(void)
{
    char month[INPUT_SIZE];

    if (!read_line(stdin, month, sizeof month)) {
        fputs("Failed to read the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");

    return EXIT_SUCCESS;
}