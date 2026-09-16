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
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) {
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

    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char month[32];

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return 1;
    }

    size_t length = strlen(month);

    if (length > 0 && month[length - 1] == '\n') {
        month[length - 1] = '\0';
    } else if (length == sizeof(month) - 1) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}