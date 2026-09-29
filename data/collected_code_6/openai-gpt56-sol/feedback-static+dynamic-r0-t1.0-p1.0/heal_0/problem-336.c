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

static bool month_contains_28_days(const char *month)
{
    static const char *const months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if (month == NULL) {
        return false;
    }

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
        fprintf(stderr, "Failed to read the month name.\n");
        return 1;
    }

    size_t newline = strcspn(month, "\r\n");
    if (month[newline] == '\0' && newline == sizeof(month) - 1U) {
        fprintf(stderr, "Month name is too long.\n");
        return 1;
    }
    month[newline] = '\0';

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        return 1;
    }

    if (month_contains_28_days(month)) {
        printf("%s contains 28 days.\n", month);
        return 0;
    }

    fprintf(stderr, "Invalid month name.\n");
    return 1;
}