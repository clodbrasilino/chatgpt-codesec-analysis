#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LENGTH 4096U

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) !=
            tolower((unsigned char)*right)) {
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

    for (size_t i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_remainder(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stream);
}

static char *read_line(FILE *stream)
{
    char *line;
    size_t length = 0U;
    bool complete = false;
    int character;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(MAXIMUM_LENGTH + 1U);
    if (line == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            complete = true;
            break;
        }

        if (length == MAXIMUM_LENGTH) {
            if (!discard_remainder(stream)) {
                free(line);
                return NULL;
            }

            free(line);
            return NULL;
        }

        line[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stream) || length == 0U) {
            free(line);
            return NULL;
        }

        complete = true;
    }

    if (!complete) {
        free(line);
        return NULL;
    }

    if (length > 0U && line[length - 1U] == '\r') {
        --length;
    }

    line[length] = '\0';

    {
        char *resized = realloc(line, length + 1U);

        if (resized != NULL) {
            line = resized;
        }
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