#include <stdio.h>
#include <stdlib.h>

static void remove_multiple_spaces(char *str)
{
    char *read = str;
    char *write = str;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (*read != ' ' || !previous_was_space) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write++ = *read;
        }

        previous_was_space = (*read == ' ');
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ++read;
    }

    *write = '\0';
}

int main(void)
{
    char *text = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_text;

            if (new_capacity <= capacity) {
                free(text);
                return 1;
            }

            new_text = realloc(text, new_capacity);
            if (new_text == NULL) {
                free(text);
                return 1;
            }

            text = new_text;
            capacity = new_capacity;
        }

        text[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(text);
        return 1;
    }

    if (length == 0) {
        free(text);
        return 0;
    }

    text[length] = '\0';
    remove_multiple_spaces(text);

    if (fputs(text, stdout) == EOF) {
        free(text);
        return 1;
    }

    free(text);
    return 0;
}