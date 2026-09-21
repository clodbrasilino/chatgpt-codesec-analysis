#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str != 'a') {
        return false;
    }

    ++str;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != '\r' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(input);
            return 1;
        }

        if (length == 0) {
            free(input);
            return 0;
        }
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return 1;
        }

        input = new_input;
    }

    input[length] = '\0';

    puts(matches_pattern(input) ? "Match" : "No match");

    free(input);
    return 0;
}