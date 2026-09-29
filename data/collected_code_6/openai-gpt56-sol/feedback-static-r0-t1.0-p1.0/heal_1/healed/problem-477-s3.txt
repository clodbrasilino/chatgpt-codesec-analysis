#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (char *p = string; *p != '\0'; ++p) {
        *p = (char)tolower((unsigned char)*p);
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            char *new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return 1;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(string);
        return 1;
    }

    if (length == 0) {
        free(string);
        return 0;
    }

    string[length] = '\0';

    if (string_to_lower(string) != 0) {
        free(string);
        return 1;
    }

    if (fputs(string, stdout) == EOF) {
        free(string);
        return 1;
    }

    free(string);
    return 0;
}