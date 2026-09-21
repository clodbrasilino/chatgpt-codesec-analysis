#include <stdio.h>
#include <stdlib.h>

static int remove_spaces(char *string)
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
    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int ch;

    string = malloc(capacity);
    if (string == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > (size_t)-1 / 2) {
                fprintf(stderr, "Input is too large.\n");
                free(string);
                return 1;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                fprintf(stderr, "Failed to allocate memory.\n");
                free(string);
                return 1;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        free(string);
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(string);
        return 0;
    }

    string[length] = '\0';
    remove_spaces(string);

    if (printf("%s\n", string) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        free(string);
        return 1;
    }

    free(string);
    return 0;
}