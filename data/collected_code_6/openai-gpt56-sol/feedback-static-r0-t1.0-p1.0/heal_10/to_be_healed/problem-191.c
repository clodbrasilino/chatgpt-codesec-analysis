#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXIMUM_LENGTH 4096U

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        const unsigned char left_character = (unsigned char)*left;
        const unsigned char right_character = (unsigned char)*right;

        if (tolower(left_character) != tolower(right_character)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static bool month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
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

static bool discard_remainder(FILE *stream)
{
    if (stream == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        const int character = fgetc(stream);

        if (character == '\n') {
            return true;
        }

        if (character == EOF) {
            return ferror(stream) == 0;
        }
    }
}

static char *read_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAXIMUM_LENGTH + 2U];
    size_t length;
    char *line;

    if (stream == NULL) {
        return NULL;
    }

    if (fgets(buffer, (int)sizeof buffer, stream) == NULL) {
        return NULL;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > MAXIMUM_LENGTH) {
        if (!discard_remainder(stream)) {
            return NULL;
        }
        return NULL;
    } else if (length == MAXIMUM_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        const int next = fgetc(stream);

        if (next == EOF) {
            if (ferror(stream)) {
                return NULL;
            }
        } else if (next != '\n') {
            if (!discard_remainder(stream)) {
                return NULL;
            }
            return NULL;
        }
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
        buffer[length] = '\0';
    }

    line = malloc(length + 1U);
    if (line == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i <= length; ++i) {
        line[i] = buffer[i];
    }

    return line;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}