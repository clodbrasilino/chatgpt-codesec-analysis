#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_LINE_LENGTH = 4096
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

    if (month == NULL) {
        return -1;
    }

    const size_t month_count = sizeof months / sizeof months[0];

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

    const size_t month_count =
        sizeof has_31_days / sizeof has_31_days[0];

    return month_index >= 0 &&
           (size_t)month_index < month_count &&
           has_31_days[(size_t)month_index];
}

static bool discard_remainder(FILE *stream)
{
    if (stream == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            return true;
        }

        if (ch == EOF) {
            return feof(stream) && !ferror(stream);
        }
    }
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_LINE_LENGTH + 2];

    if (fgets(input, sizeof input, stream) == NULL) {
        return NULL;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\r') {
        if (input[length + 1] == '\n') {
            input[length] = '\0';
        } else {
            input[length] = '\0';

            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);
            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    return NULL;
                }
            } else if (next == EOF && ferror(stream)) {
                return NULL;
            }
        }
    } else if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_LINE_LENGTH) {
        if (!discard_remainder(stream)) {
            return NULL;
        }
        return NULL;
    } else if (length == MAX_LINE_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stream);

        if (next == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int following = fgetc(stream);

            if (following != '\n' && following != EOF &&
                ungetc(following, stream) == EOF) {
                return NULL;
            }

            if (following == EOF && ferror(stream)) {
                return NULL;
            }
        } else if (next != '\n' && next != EOF) {
            if (!discard_remainder(stream)) {
                return NULL;
            }
            return NULL;
        } else if (next == EOF && ferror(stream)) {
            return NULL;
        }

        input[length] = '\0';
    } else {
        input[length] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_length = strlen(input);
    char *result = malloc(result_length + 1);

    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, input, result_length + 1);
    return result;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    int month_index = find_month(month);
    free(month);

    if (month_index < 0) {
        fputs("Invalid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month_index) ? "Yes" : "No");
    return EXIT_SUCCESS;
}