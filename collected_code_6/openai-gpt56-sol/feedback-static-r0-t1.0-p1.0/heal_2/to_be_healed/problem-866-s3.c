#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum {
    MONTH_BUFFER_SIZE = 32
};

static bool equal_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int find_month(const char *month)
{
    static const char *const months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if (month == NULL) {
        return -1;
    }

    for (size_t i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equal_ignore_case(month, months[i])) {
            return (int)i;
        }
    }

    return -1;
}

static bool month_has_31_days(int month_index)
{
    static const bool has_31_days[] = {
        true, false, true, false,
        true, false, true, true,
        false, true, false, true
    };

    return month_index >= 0 &&
           (size_t)month_index < sizeof has_31_days / sizeof has_31_days[0] &&
           has_31_days[month_index];
}

static bool discard_remaining_input(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE];

    if (fgets(month, sizeof month, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    char *newline = strchr(month, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        discard_remaining_input();
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    int month_index = find_month(month);

    if (month_index < 0) {
        fputs("Invalid month name.\n", stderr);
        return 1;
    }

    puts(month_has_31_days(month_index) ? "Yes" : "No");
    return 0;
}