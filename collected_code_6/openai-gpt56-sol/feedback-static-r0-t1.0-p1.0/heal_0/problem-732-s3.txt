#include <stdio.h>
#include <stdlib.h>

void replace_delimiters(char *text)
{
    if (text == NULL) {
        return;
    }

    for (; *text != '\0'; ++text) {
        if (*text == ' ' || *text == ',' || *text == '.') {
            *text = ':';
        }
    }
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

    replace_delimiters(line);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}