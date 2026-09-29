#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void remove_whitespace(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if (!isspace((unsigned char)*source)) {
            *destination++ = *source;
        }
        source++;
    }

    *destination = '\0';
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    remove_whitespace(line);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}