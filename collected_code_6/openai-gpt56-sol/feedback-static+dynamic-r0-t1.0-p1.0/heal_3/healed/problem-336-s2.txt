#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { MAX_MONTH_LENGTH = 31 };

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_character = (unsigned char)*left;
        unsigned char right_character = (unsigned char)*right;

        if (tolower(left_character) != tolower(right_character)) {
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
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return !ferror(stdin);
}

static bool read_month(char *month, size_t capacity)
{
    size_t length;

    if (month == NULL || capacity < MAX_MONTH_LENGTH + 1U) {
        return false;
    }

    if (fgets(month, (int)capacity, stdin) == NULL) {
        return false;
    }

    length = strcspn(month, "\r\n");

    if (month[length] == '\0') {
        if (!feof(stdin)) {
            if (!discard_line()) {
                return false;
            }
            return false;
        }
    } else if (month[length] == '\r' && month[length + 1U] == '\0') {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return false;
            }
        }
    }

    month[length] = '\0';
    return true;
}

int main(void)
{
    char month[MAX_MONTH_LENGTH + 1U];

    if (!read_month(month, sizeof month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");
    return EXIT_SUCCESS;
}