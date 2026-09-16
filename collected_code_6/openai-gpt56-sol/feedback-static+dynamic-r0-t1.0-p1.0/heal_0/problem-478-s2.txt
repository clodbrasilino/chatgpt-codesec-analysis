#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_lowercase_substrings(char *string)
{
    size_t read_index = 0;
    size_t write_index = 0;

    while (string[read_index] != '\0') {
        unsigned char character = (unsigned char)string[read_index];

        if (islower(character) == 0) {
            string[write_index++] = string[read_index];
        }

        ++read_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);

        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (length > 0 && line[(size_t)length - 1] == '\n') {
        line[(size_t)length - 1] = '\0';
    }

    remove_lowercase_substrings(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}