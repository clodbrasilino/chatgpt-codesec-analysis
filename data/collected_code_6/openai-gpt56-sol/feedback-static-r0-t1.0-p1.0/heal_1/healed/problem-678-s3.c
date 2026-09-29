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

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return 1;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return 1;
            }

            string = temporary;
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