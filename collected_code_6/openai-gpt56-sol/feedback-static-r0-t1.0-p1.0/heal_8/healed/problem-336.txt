#include <ctype.h>
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

static bool read_month(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    size_t length = 0U;
    int ch = EOF;
    bool too_long = false;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (length + 1U < capacity) {
                    buffer[length++] = (char)ch;
                } else {
                    too_long = true;
                }

                ch = next;

                if (length + 1U < capacity) {
                    buffer[length++] = (char)ch;
                } else {
                    too_long = true;
                }

                continue;
            }

            ch = next;
            break;
        }

        if (length + 1U < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    buffer[length] = '\0';

    if (ferror(stdin) || too_long || length == 0U) {
        buffer[0] = '\0';
        return false;
    }

    return ch == '\n' || ch == EOF;
}

int main(void)
{
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