#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define MONTH_BUFFER_SIZE 32U

static bool equals_ignore_case(const char *left, const char *right)
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

    for (size_t i = 0U; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return !ferror(stdin);
        }
    }

    return true;
}

static bool read_month(char *buffer, size_t capacity)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    char *newline = strchr(buffer, '\n');

    if (newline != NULL) {
        if (newline > buffer && newline[-1] == '\r') {
            newline[-1] = '\0';
        } else {
            *newline = '\0';
        }
    } else if (!feof(stdin)) {
        buffer[0] = '\0';
        (void)discard_line();
        return false;
    }

    if (ferror(stdin) || buffer[0] == '\0') {
        buffer[0] = '\0';
        return false;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE];

    if (!read_month(month, sizeof month)) {
        fputs("Failed to read the month name or input is too long.\n", stderr);
        return 1;
    }

    if (!month_contains_28_days(month)) {
        fputs("Invalid month name.\n", stderr);
        return 1;
    }

    printf("%s contains 28 days.\n", month);
    return 0;
}