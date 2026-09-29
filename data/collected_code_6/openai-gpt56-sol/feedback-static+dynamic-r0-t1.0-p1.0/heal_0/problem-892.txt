#include <stdio.h>
#include <stdlib.h>

static void remove_multiple_spaces(char *str)
{
    char *read_ptr = str;
    char *write_ptr = str;
    int previous_was_space = 0;

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ' || !previous_was_space) {
            *write_ptr++ = *read_ptr;
        }

        previous_was_space = (*read_ptr == ' ');
        read_ptr++;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    remove_multiple_spaces(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}