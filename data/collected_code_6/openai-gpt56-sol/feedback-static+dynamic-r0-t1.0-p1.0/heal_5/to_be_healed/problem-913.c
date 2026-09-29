#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0U &&
           isdigit((unsigned char)str[length - 1U]) != 0;
}

int main(void)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *input = malloc(capacity);
    int ch = EOF;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF || ch == '\n' || ch == '\r') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = getchar();

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                free(input);
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    if (puts(ends_with_number(input, length) ? "true" : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}