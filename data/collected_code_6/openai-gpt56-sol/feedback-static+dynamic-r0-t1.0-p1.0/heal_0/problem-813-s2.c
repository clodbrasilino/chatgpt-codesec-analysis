#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t string_length(const char *string)
{
    const char *cursor = string;

    while (*cursor != '\0') {
        ++cursor;
    }

    return (size_t)(cursor - string);
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t characters_read = getline(&line, &capacity, stdin);

    if (characters_read < 0) {
        free(line);

        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (characters_read > 0 && line[characters_read - 1] == '\n') {
        line[characters_read - 1] = '\0';
    }

    printf("%zu\n", string_length(line));
    free(line);

    return EXIT_SUCCESS;
}