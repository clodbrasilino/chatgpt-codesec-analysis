#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { MONTH_BUFFER_SIZE = 32 };

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_character = (unsigned char)*left;
        unsigned char right_character = (unsigned char)*right;

        if (tolower(left_character) != tolower(right_character)) {
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

static bool discard_line_remainder(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character == '\n' || feof(stdin);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE];

    if (fgets(month, sizeof month, stdin) == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return 1;
    }

    size_t length = strcspn(month, "\r\n");

    if (month[length] == '\0' && length == sizeof month - 1U) {
        if (!discard_line_remainder()) {
            fputs("Failed to process the input.\n", stderr);
            return 1;
        }

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    month[length] = '\0';

    if (length == 0U) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");
    return 0;
}