#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_spaces(char *string)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

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
    size_t length = 0;
    size_t capacity = 128;
    int character;

    string = malloc(capacity);
    if (string == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (size_t)-1 / 2) {
                free(string);
                return 1;
            }

            new_capacity = capacity * 2;
            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return 1;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(string);
        return 1;
    }

    if (character == EOF && length == 0) {
        free(string);
        return 0;
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