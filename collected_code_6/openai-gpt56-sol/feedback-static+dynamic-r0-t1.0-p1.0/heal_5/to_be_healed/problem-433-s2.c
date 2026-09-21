#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_greater_than_all(int number, const int array[], size_t length)
{
    if (array == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (number <= array[i]) {
            return false;
        }
    }

    return true;
}

static bool discard_remaining_input(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' || feof(stdin);
}

static bool read_int(int *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    char *end;
    long parsed;
    bool valid = false;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    discard_remaining_input();
                    free(line);
                    return false;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX - 1U) {
                discard_remaining_input();
                free(line);
                return false;
            }

            new_line = realloc(line, new_capacity + 1U);
            if (new_line == NULL) {
                discard_remaining_input();
                free(line);
                return false;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(line);
        return false;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            return false;
        }
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtol(line, &end, 10);

    if (end != line && errno != ERANGE &&
        parsed >= INT_MIN && parsed <= INT_MAX) {
        while (*end != '\0' && isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = (int)parsed;
            valid = true;
        }
    }

    free(line);
    return valid;
}

int main(void)
{
    const int array[] = {3, 7, 12, 18, 25};
    const size_t length = sizeof array / sizeof array[0];
    int number;

    if (fputs("Enter an integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_int(&number)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_greater_than_all(number, array, length)) {
        if (printf("%d is greater than every array element.\n", number) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%d is not greater than every array element.\n", number) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}