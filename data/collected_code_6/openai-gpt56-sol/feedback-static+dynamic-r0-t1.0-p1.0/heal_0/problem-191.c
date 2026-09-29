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

static bool month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };
    size_t index;

    if (month == NULL) {
        return false;
    }

    for (index = 0; index < sizeof(months) / sizeof(months[0]); ++index) {
        if (equals_ignore_case(month, months[index])) {
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

    month[strcspn(month, "\r\n")] = '\0';

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        return 1;
    }

    printf("%s\n", month_has_30_days(month) ? "Yes" : "No");

    return 0;
}