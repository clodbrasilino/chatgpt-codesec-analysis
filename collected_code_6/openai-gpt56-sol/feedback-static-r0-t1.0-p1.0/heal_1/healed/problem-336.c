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

    for (size_t i = 0; i < sizeof months / sizeof months[0]; ++i) {
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

    if (fgets(buffer, capacity, stdin) == NULL) {
        return false;
    }

    size_t length = strcspn(buffer, "\r\n");

    if (buffer[length] != '\0') {
        buffer[length] = '\0';
        return true;
    }

    if (length == capacity - 1U && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        buffer[0] = '\0';
        return false;
    }

    return true;
}

int main(void)
{
    char month[32];

    if (!read_month(month, sizeof month)) {
        fprintf(stderr, "Failed to read the month name or input is too long.\n");
        return 1;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        return 1;
    }

    if (!month_contains_28_days(month)) {
        fprintf(stderr, "Invalid month name.\n");
        return 1;
    }

    printf("%s contains 28 days.\n", month);
    return 0;
}