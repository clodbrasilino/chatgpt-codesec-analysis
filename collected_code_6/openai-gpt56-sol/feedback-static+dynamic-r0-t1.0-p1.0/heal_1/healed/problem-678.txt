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
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);

    if (string == NULL) {
        return 1;
    }

    for (;;) {
        int character = getchar();

        if (character == EOF || character == '\n') {
            if (character == EOF && ferror(stdin)) {
                free(string);
                return 1;
            }
            break;
        }

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

    string[length] = '\0';
    remove_spaces(string);

    if (puts(string) == EOF) {
        free(string);
        return 1;
    }

    free(string);
    return 0;
}