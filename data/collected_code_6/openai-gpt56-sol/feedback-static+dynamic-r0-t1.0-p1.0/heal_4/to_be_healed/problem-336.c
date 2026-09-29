#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static bool month_contains_28_days(const char *month)
{
    static const char *const months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if (month == NULL) {
        return false;
    }

    const size_t month_count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 16U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return NULL;
                }
            } else if (next == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2U;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fprintf(stderr, "Failed to read the month name.\n");
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        free(month);
        return EXIT_FAILURE;
    }

    if (!month_contains_28_days(month)) {
        fprintf(stderr, "Invalid month name.\n");
        free(month);
        return EXIT_FAILURE;
    }

    printf("%s contains 28 days.\n", month);
    free(month);

    return EXIT_SUCCESS;
}