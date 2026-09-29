#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int equals_ignore_case(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }

    while (*first != '\0' && *second != '\0') {
        if (tolower((unsigned char)*first) != tolower((unsigned char)*second)) {
            return 0;
        }
        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

static int month_has_31_days(const char *month)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32];
    size_t length;

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Failed to read the month name.\n");
        return 1;
    }

    length = strcspn(month, "\r\n");
    if (month[length] == '\0' && length == sizeof(month) - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        fprintf(stderr, "Month name is too long.\n");
        return 1;
    }

    month[length] = '\0';

    if (length == 0U) {
        fprintf(stderr, "Month name cannot be empty.\n");
        return 1;
    }

    printf("%s\n", month_has_31_days(month) ? "Yes" : "No");
    return 0;
}