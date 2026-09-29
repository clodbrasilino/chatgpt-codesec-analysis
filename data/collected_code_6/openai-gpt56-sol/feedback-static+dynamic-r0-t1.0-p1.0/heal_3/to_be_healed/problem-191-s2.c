#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) !=
            tolower((unsigned char)*right)) {
            return 0;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 16;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (month_has_30_days(month)) {
        puts("The month has 30 days.");
    } else {
        puts("The month does not have 30 days.");
    }

    free(month);
    return EXIT_SUCCESS;
}