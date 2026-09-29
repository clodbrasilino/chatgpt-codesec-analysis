#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_INPUT_LENGTH = 128,
    BUFFER_SIZE = MAX_INPUT_LENGTH + 2
};

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

    const size_t month_count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_remainder(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return character == '\n' || !ferror(stdin);
}

static bool consume_line_ending_or_eof(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int character = getchar();

    if (character == '\n') {
        return true;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = getchar();

        if (next == '\n') {
            return true;
        }

        if (next == EOF) {
            return !ferror(stdin);
        }

        return ungetc(next, stdin) != EOF;
    }

    if (character == EOF) {
        return !ferror(stdin);
    }

    if (!discard_remainder()) {
        return false;
    }

    return false;
}

static bool read_line(char **line)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    size_t length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r' || buffer[length] == '\n') {
        if (buffer[length] == '\r' && buffer[length + 1] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                return false;
            }

            if (next == EOF && ferror(stdin)) {
                return false;
            }
        }

        buffer[length] = '\0';
    } else {
        if (length > MAX_INPUT_LENGTH) {
            if (!discard_remainder()) {
                return false;
            }

            return false;
        }

        if (length == MAX_INPUT_LENGTH && !consume_line_ending_or_eof()) {
            return false;
        }
    }

    if (length == 0 || length > MAX_INPUT_LENGTH) {
        return false;
    }

    char *result = malloc(length + 1);

    if (result == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, buffer, length + 1);
    *line = result;

    return true;
}

int main(void)
{
    char *month = NULL;

    if (!read_line(&month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}