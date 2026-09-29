#include <stdio.h>
#include <stdlib.h>

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return 0;
        }
        ++str;
    }

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(input);
                    return 1;
                }
            }
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > (size_t)-1 / 2) {
                free(input);
                return 1;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    if (character == EOF && length == 0) {
        free(input);
        return 1;
    }

    input[length] = '\0';

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");

    free(input);
    return 0;
}