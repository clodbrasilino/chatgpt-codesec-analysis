#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

static bool discard_line_remainder(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || (ch == EOF && !ferror(stdin));
}

static bool read_month(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t length = strcspn(buffer, "\r\n");
    char terminator = buffer[length];

    if (terminator != '\0') {
        buffer[length] = '\0';

        if (terminator == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    buffer[0] = '\0';
                    return false;
                }
            } else if (next == EOF && ferror(stdin)) {
                buffer[0] = '\0';
                return false;
            }
        }

        return length > 0U;
    }

    if (length == capacity - 1U) {
        if (!discard_line_remainder()) {
            buffer[0] = '\0';
        }
        return false;
    }

    return length > 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE] = {0};

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