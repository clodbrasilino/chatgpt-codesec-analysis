#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

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

static bool month_has_28_days(const char *month)
{
    return equals_ignore_case(month, "February");
}

static bool discard_remaining_input(FILE *stream)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
    }

    return character != EOF || !ferror(stream);
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    char *line = malloc(MAX_INPUT_LENGTH + 2);

    if (line == NULL) {
        return NULL;
    }

    if (fgets(line, MAX_INPUT_LENGTH + 2, stream) == NULL) {
        free(line);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(line);

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';

        if (length > 0 && line[length - 1] == '\r') {
            line[--length] = '\0';
        }
    } else if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        free(line);
        return NULL;
    } else if (!feof(stream) && !discard_remaining_input(stream)) {
        free(line);
        return NULL;
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

    puts(month_has_28_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}