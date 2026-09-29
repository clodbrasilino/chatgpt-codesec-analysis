#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n' || feof(stdin);
}

static bool read_month(char *month, size_t capacity)
{
    size_t length;

    if (month == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
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
    } else {
        /* Possible weaknesses found:
         *  Assignment 'month[length]='\0'', assigned value is 0
         */
        month[length] = '\0';

        /* Possible weaknesses found:
         *  Condition 'month[length]=='\r'' is always false
         *  Condition 'month[length]=='\r'' is always false [knownConditionTrueFalse]
         */
        if (month[length] == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                if (ungetc(character, stdin) == EOF) {
                    return false;
                }
            }

            if (ferror(stdin)) {
                return false;
            }
        }
    }

    month[length] = '\0';
    return true;
}

int main(void)
{
    char *month = malloc((size_t)MAX_MONTH_LENGTH + 1U);

    if (month == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_month(month, (size_t)MAX_MONTH_LENGTH + 1U)) {
        fputs("Failed to read a valid month name.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}