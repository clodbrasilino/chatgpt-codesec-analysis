#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t length_of_last_word(const char *str)
{
    size_t last_length = 0;
    size_t current_length = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }
        ++str;
    }

    return current_length != 0 ? current_length : last_length;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
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

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';
    printf("%zu\n", length_of_last_word(input));

    free(input);
    return 0;
}