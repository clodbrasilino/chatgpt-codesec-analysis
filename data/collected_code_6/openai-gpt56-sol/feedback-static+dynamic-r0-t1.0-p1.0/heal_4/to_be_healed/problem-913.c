#include <ctype.h>
#include <stdbool.h>
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
    int ch;

    if (input == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return 1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
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

        if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
            free(input);
            return 1;
        }
    }

    if (ferror(stdin) != 0) {
        free(input);
        return 1;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        return 0;
    }

    input[length] = '\0';

    if (printf("%s\n", ends_with_number(input, length) ? "true" : "false") < 0) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}