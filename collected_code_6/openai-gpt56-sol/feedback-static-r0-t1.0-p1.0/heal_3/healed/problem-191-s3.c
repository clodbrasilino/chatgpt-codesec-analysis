#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32U

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return 0;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0U; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n') {
        if (character == EOF) {
            return ferror(stdin) == 0;
        }
    }

    return 1;
}

int main(void)
{
    char month[MONTH_BUFFER_SIZE];

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    char *newline = memchr(month, '\n', sizeof(month));

    if (newline != NULL) {
        *newline = '\0';

        if (newline > month && newline[-1] == '\r') {
            newline[-1] = '\0';
        }
    } else {
        size_t length = strnlen(month, sizeof(month));

        if (length == sizeof(month)) {
            fputs("Invalid input.\n", stderr);
            return 1;
        }

        if (!feof(stdin)) {
            if (!discard_line()) {
                fputs("Failed to read the month.\n", stderr);
                return 1;
            }

            fputs("Month name is too long.\n", stderr);
            return 1;
        }
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}