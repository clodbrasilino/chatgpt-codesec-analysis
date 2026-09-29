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

    for (size_t i = 0U; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int discard_line(void)
{
    char buffer[128];

    while (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 1;
        }
    }

    return feof(stdin) != 0;
}

int main(void)
{
    char month[MONTH_BUFFER_SIZE];

    if (fgets(month, (int)sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    size_t length = strlen(month);

    if (length > 0U && month[length - 1U] == '\n') {
        month[--length] = '\0';

        if (length > 0U && month[length - 1U] == '\r') {
            month[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        discard_line();
        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (length == 0U) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}