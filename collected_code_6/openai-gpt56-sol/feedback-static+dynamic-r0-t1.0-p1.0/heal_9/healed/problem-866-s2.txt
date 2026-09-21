#include <ctype.h>
#include <stdbool.h>
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

    size_t month_count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_remainder(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character != EOF || !ferror(stdin);
}

static bool read_line(char **line)
{
    enum {
        MAX_INPUT_LENGTH = 128,
        BUFFER_SIZE = MAX_INPUT_LENGTH + 2
    };

    char buffer[BUFFER_SIZE];

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    size_t length = 0;

    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n' && buffer[length] != '\r') {
        ++length;
    }

    if (length == sizeof buffer) {
        return false;
    }

    if (buffer[length] == '\r') {
        if (buffer[length + 1] == '\n') {
            buffer[length + 1] = '\0';
        } else if (buffer[length + 1] == '\0') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return false;
                }
            }

            if (next == EOF && ferror(stdin)) {
                return false;
            }
        }
    }

    if (buffer[length] == '\n' || buffer[length] == '\r') {
        buffer[length] = '\0';
    } else if (length == MAX_INPUT_LENGTH + 1) {
        if (!discard_remainder()) {
            return false;
        }
        return false;
    } else if (length == MAX_INPUT_LENGTH) {
        int next = fgetc(stdin);

        if (next == '\r') {
            int after_cr = fgetc(stdin);

            if (after_cr != '\n' && after_cr != EOF) {
                if (ungetc(after_cr, stdin) == EOF) {
                    return false;
                }
            }

            if (after_cr == EOF && ferror(stdin)) {
                return false;
            }
        } else if (next != '\n' && next != EOF) {
            if (!discard_remainder()) {
                return false;
            }
            return false;
        } else if (next == EOF && ferror(stdin)) {
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

    for (size_t i = 0; i <= length; ++i) {
        result[i] = buffer[i];
    }

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