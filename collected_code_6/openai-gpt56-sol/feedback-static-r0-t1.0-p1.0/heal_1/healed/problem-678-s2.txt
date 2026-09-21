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
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(string);
                fprintf(stderr, "Input is too large.\n");
                return 1;
            }

            char *temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                fprintf(stderr, "Failed to allocate memory.\n");
                return 1;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(string);
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(string);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *temporary = realloc(string, new_capacity);

        if (temporary == NULL) {
            free(string);
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }

        string = temporary;
        capacity = new_capacity;
    }

    string[length] = '\0';
    remove_spaces(string);

    if (printf("%s\n", string) < 0) {
        free(string);
        fprintf(stderr, "Failed to write output.\n");
        return 1;
    }

    free(string);
    return 0;
}