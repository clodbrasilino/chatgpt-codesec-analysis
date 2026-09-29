#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL) {
        return 0;
    }

    n = (uintmax_t)length;

    if (n != 0 && n > (UINTMAX_MAX - 1) / n) {
        return 0;
    }

    *count = n * (n + 1) / 2;
    return 1;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);
    uintmax_t count;
    int ch;

    if (input == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            return 1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    input[length] = '\0';

    if (!count_nonempty_substrings(length, &count)) {
        free(input);
        return 1;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}