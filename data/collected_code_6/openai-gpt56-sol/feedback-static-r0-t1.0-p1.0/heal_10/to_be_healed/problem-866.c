#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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

    for (i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int read_month(char **month)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    if (month == NULL) {
        return 0;
    }

    *month = NULL;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length > SIZE_MAX - 2) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;
            char *new_line;

            if (new_capacity <= capacity || new_capacity < length + 2) {
                free(line);
                return -1;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(line);
        return 0;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    if (length == 0) {
        free(line);
        return 0;
    }

    line[length] = '\0';
    *month = line;
    return 1;
}

int main(void)
{
    char *month;
    int status = read_month(&month);

    if (status < 0) {
        fputs("Failed to allocate memory for the month name.\n", stderr);
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
    free(month);
    return 0;
}