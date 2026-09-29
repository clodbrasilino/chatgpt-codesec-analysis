#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_even_characters(char *string)
{
    size_t read_index = 0;
    size_t write_index = 0;

    while (string[read_index] != '\0') {
        if (read_index % 2U == 0U) {
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
        return EXIT_FAILURE;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[(size_t)length - 1U] = '\0';
    }

    remove_even_characters(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}