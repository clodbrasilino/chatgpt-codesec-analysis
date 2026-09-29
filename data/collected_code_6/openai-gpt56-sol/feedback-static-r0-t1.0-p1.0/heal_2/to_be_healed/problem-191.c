#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    for (size_t index = 0; index < sizeof(months) / sizeof(months[0]); ++index) {
        if (equals_ignore_case(month, months[index])) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF || character == '\n') {
            if (character == EOF && length == 0) {
                free(line);
                return NULL;
            }
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(line);
                return NULL;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fprintf(stderr, "Failed to read the month name.\n");
        return 1;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        free(month);
        return 1;
    }

    printf("%s\n", month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return 0;
}