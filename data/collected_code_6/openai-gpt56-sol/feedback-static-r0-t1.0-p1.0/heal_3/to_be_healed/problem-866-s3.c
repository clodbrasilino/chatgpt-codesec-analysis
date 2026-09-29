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
    const size_t month_count = sizeof months / sizeof months[0];

    if (month == NULL) {
        return -1;
    }

    for (size_t i = 0; i < month_count; ++i) {
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
    const size_t month_count = sizeof has_31_days / sizeof has_31_days[0];

    return month_index >= 0 &&
           (size_t)month_index < month_count &&
           has_31_days[month_index];
}

static bool read_month(char *buffer, size_t buffer_size)
{
    if (buffer == NULL || buffer_size < 2) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    size_t length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r' || buffer[length] == '\n') {
        buffer[length] = '\0';

        if (buffer[length + 1] == '\n') {
            buffer[length + 1] = '\0';
        }

        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int character;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE] = {0};

    if (!read_month(month, sizeof month)) {
        fputs(feof(stdin) ? "Failed to read input.\n" : "Input is too long.\n",
              stderr);
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