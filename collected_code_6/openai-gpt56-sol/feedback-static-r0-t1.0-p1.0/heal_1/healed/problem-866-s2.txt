#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

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

    size_t month_count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char month[32];

    if (fgets(month, sizeof month, stdin) == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return 1;
    }

    size_t length = 0;
    while (length < sizeof month && month[length] != '\0' &&
           month[length] != '\n') {
        ++length;
    }

    if (length < sizeof month && month[length] == '\n') {
        month[length] = '\0';
    } else if (length == sizeof month - 1) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}