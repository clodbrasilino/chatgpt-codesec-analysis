#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_integer(const char *str)
{
    const unsigned char *p;

    if (str == NULL || *str == '\0') {
        return false;
    }

    p = (const unsigned char *)str;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (*p == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }
        ++p;
    }

    return true;
}

int main(void)
{
    char *input;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        char *temporary;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity || new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (puts(is_integer(input) ? "true" : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}