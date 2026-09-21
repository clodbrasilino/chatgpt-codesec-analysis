#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool matches(const char *str)
{
    if (str == NULL || *str++ != 'a' || *str != 'b') {
        return false;
    }

    do {
        ++str;
    } while (*str == 'b');

    return *str == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
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

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return 0;
    }

    if (capacity == 0) {
        input = malloc(1);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");

    free(input);
    return 0;
}