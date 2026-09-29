#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

static bool all_characters_same(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    const char first = *str++;

    while (*str != '\0') {
        if (*str++ != first) {
            return false;
        }
    }

    return true;
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
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("No input provided.\n", stderr);
        return 1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return 1;
        }

        char *new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return 1;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity++;
    }

    input[length] = '\0';

    if (all_characters_same(input)) {
        puts("All characters are the same.");
    } else {
        puts("Not all characters are the same.");
    }

    free(input);
    return 0;
}