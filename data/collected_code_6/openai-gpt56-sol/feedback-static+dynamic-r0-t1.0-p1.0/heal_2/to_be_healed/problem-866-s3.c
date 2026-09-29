#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

static bool month_has_31_days(const char *month)
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

    const size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < count; ++i) {
        if (equal_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool is_valid_month(const char *month)
{
    static const char *const months[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    const size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < count; ++i) {
        if (equal_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    char *newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';

        size_t length = (size_t)(newline - buffer);
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int character;
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32] = {0};

    if (!read_line(month, sizeof(month))) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }
        return 1;
    }

    if (!is_valid_month(month)) {
        fputs("Invalid month name.\n", stderr);
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}