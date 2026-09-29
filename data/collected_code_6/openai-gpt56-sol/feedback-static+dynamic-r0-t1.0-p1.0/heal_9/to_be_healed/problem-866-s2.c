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

static bool read_line(char **line)
{
    enum { INITIAL_CAPACITY = 32, MAX_INPUT_LENGTH = 128 };

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }

            if (next == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }

            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = getchar();
            } while (character != '\n' && character != EOF);

            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity > MAX_INPUT_LENGTH + 1) {
                new_capacity = MAX_INPUT_LENGTH + 1;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (length == 0) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';

    char *result = realloc(buffer, length + 1);

    if (result == NULL) {
        result = buffer;
    }

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