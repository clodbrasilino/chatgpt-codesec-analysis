#include <stdio.h>
#include <stdlib.h>

static void remove_spaces(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_string = realloc(string, new_capacity);

            if (new_string == NULL) {
                free(string);
                return 1;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(string);
        return 1;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return 1;
        }
    }

    string[length] = '\0';
    remove_spaces(string);

    if (puts(string) == EOF) {
        free(string);
        return 1;
    }

    free(string);
    return 0;
}