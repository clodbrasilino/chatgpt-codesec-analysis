#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    const size_t month_count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 128 };

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    char buffer[MAX_INPUT_LENGTH + 2];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    size_t length = 0;

    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n' && buffer[length] != '\r') {
        ++length;
    }

    if (length == MAX_INPUT_LENGTH + 1) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return false;
    }

    if (buffer[length] == '\0' && length == MAX_INPUT_LENGTH) {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            return false;
        }

        if (character == EOF && ferror(stdin)) {
            return false;
        }
    }

    if (length == 0) {
        return false;
    }

    char *result = malloc(length + 1);

    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = buffer[i];
    }

    result[length] = '\0';
    *line = result;
    return true;
}

int main(void)
{
    char *month = NULL;

    if (!read_line(&month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}