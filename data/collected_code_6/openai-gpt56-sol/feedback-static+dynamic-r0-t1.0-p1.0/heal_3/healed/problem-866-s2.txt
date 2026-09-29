#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        return false;
    }

    size_t length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int character;
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char month[32];

    if (!read_line(month, sizeof month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}