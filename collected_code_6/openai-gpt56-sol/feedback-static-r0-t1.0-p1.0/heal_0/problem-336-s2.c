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

static bool month_has_28_days(const char *month)
{
    return equals_ignore_case(month, "February");
}

int main(void)
{
    char month[32];

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return 1;
    }

    size_t newline_index = strcspn(month, "\r\n");

    if (month[newline_index] == '\0' && !feof(stdin)) {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    month[newline_index] = '\0';

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    printf("%s\n", month_has_28_days(month) ? "Yes" : "No");
    return 0;
}