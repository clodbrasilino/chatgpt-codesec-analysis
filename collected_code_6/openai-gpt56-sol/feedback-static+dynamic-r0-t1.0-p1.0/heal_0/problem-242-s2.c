#include <stdio.h>
#include <stdlib.h>

static size_t count_characters(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (string[count] != '\0') {
        ++count;
    }

    return count;
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

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    printf("%zu\n", count_characters(line));

    free(line);
    return EXIT_SUCCESS;
}