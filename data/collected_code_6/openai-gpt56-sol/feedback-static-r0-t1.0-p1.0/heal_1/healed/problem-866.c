#include <ctype.h>
#include <stdio.h>
#include <string.h>

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
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    enum { MONTH_BUFFER_SIZE = 32 };
    char month[MONTH_BUFFER_SIZE];
    size_t length;
    int character;

    if (fgets(month, sizeof month, stdin) == NULL) {
        fprintf(stderr, "Failed to read the month name.\n");
        return 1;
    }

    length = strcspn(month, "\r\n");

    if (month[length] == '\0') {
        if (length == sizeof month - 1U) {
            character = getchar();

            if (character != '\n' && character != EOF) {
                while ((character = getchar()) != '\n' && character != EOF) {
                }

                fprintf(stderr, "Month name is too long.\n");
                return 1;
            }
        }
    } else {
        month[length] = '\0';

        if (month[length + 1U] == '\r' && month[length + 2U] == '\n') {
            month[length + 1U] = '\0';
        }
    }

    if (length == 0U) {
        fprintf(stderr, "Month name cannot be empty.\n");
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}