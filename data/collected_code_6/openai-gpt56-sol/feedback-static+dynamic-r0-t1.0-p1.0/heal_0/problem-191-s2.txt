#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) {
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

int main(void)
{
    char month[32];

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fputs("Input error\n", stderr);
        return 1;
    }

    month[strcspn(month, "\r\n")] = '\0';

    if (month_has_30_days(month)) {
        puts("The month has 30 days.");
    } else {
        puts("The month does not have 30 days.");
    }

    return 0;
}