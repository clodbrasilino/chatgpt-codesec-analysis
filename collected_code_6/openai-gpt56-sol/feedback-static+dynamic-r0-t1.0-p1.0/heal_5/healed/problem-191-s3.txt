#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32

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
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int discard_remaining_input(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char month[MONTH_BUFFER_SIZE];
    char *newline;
    size_t length;

    if (fgets(month, (int)sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    newline = memchr(month, '\n', sizeof(month));

    if (newline != NULL) {
        *newline = '\0';

        if (newline > month && newline[-1] == '\r') {
            newline[-1] = '\0';
        }
    } else if (!feof(stdin)) {
        if (discard_remaining_input() != 0) {
            fputs("Failed to read the month.\n", stderr);
            return 1;
        }

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    length = strnlen(month, sizeof(month));

    if (length == sizeof(month)) {
        fputs("Invalid month input.\n", stderr);
        return 1;
    }

    if (length == 0) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}