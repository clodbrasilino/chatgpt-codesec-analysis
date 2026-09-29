#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int last_digit(long long number)
{
    int digit = (int)(number % 10);
    return digit < 0 ? -digit : digit;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    long long number;
    char *end;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (SIZE_MAX / 2)) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%d\n", last_digit(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}