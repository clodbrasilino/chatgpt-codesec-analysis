#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_whitespace(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        if (!isspace(character)) {
            *destination++ = (char)character;
        }
    }

    *destination = '\0';
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length == -1) {
        free(line);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    remove_whitespace(line);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}