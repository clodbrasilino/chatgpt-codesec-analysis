#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'EXIT_FAILURE' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
  */

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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MAX_MONTH_LENGTH + 1U];

    if (!read_month(month, sizeof month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'EXIT_FAILURE' undeclared (first use in this function)
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");
    /* Possible weaknesses found:
     *  'EXIT_SUCCESS' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
     *  'EXIT_SUCCESS' undeclared (first use in this function)
     *  use of undeclared identifier 'EXIT_SUCCESS'
     */
    return EXIT_SUCCESS;
}