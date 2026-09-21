#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32U

static int equals_ignore_case(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

        if (tolower(first_char) != tolower(second_char)) {
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

    const size_t month_count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);

    return ferror(stdin) ? 0 : 1;
}

static int read_month(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    size_t length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r' || buffer[length] == '\n') {
        buffer[length] = '\0';
        return length == 0U ? 0 : 1;
    }

    if (!feof(stdin)) {
        if (!discard_line()) {
            return 0;
        }
        buffer[0] = '\0';
        return -1;
    }

    return length == 0U ? 0 : 1;
}

int main(void)
{
    char month[MONTH_BUFFER_SIZE];
    int status = read_month(month, sizeof month);

    if (status < 0) {
        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (status == 0) {
        if (ferror(stdin)) {
            fputs("Failed to read the month name.\n", stderr);
        } else {
            fputs("Month name cannot be empty.\n", stderr);
        }
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}