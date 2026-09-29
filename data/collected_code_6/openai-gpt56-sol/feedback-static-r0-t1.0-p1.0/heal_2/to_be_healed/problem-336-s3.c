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
        if (tolower((unsigned char)*left) !=
            tolower((unsigned char)*right)) {
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

static bool discard_line(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character == '\n';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32];
    char *line_end;

    if (fgets(month, sizeof month, stdin) == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return 1;
    }

    line_end = strpbrk(month, "\r\n");

    if (line_end != NULL) {
        *line_end = '\0';
    } else if (!feof(stdin)) {
        discard_line();
        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");

    return 0;
}