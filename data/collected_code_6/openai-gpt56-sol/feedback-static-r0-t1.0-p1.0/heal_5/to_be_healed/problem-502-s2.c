#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int find_remainder(int dividend, int divisor, int *remainder)
{
    if (remainder == NULL || divisor == 0) {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        *remainder = 0;
        return 1;
    }

    *remainder = dividend % divisor;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n';
}

static int read_int(const char *prompt, int *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    long parsed;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(buffer);
                    discard_line();
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                discard_line();
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return 0;
    }

    if (length == capacity) {
        char *new_buffer;

        if (capacity == (size_t)-1) {
            free(buffer);
            return 0;
        }

        new_buffer = realloc(buffer, capacity + 1);
        if (new_buffer == NULL) {
            free(buffer);
            return 0;
        }

        buffer = new_buffer;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity++;
    }

    buffer[length] = '\0';

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int)parsed;
    free(buffer);
    return 1;
}

int main(void)
{
    int dividend;
    int divisor;
    int remainder;

    if (!read_int("Enter the dividend: ", &dividend) ||
        !read_int("Enter the divisor: ", &divisor)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_remainder(dividend, divisor, &remainder)) {
        fputs("The divisor must not be zero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Remainder: %d\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}