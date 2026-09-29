#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t replace_delimiters(char *text, size_t max_replacements)
{
    size_t replacements = 0;

    if (text == NULL) {
        return 0;
    }

    for (size_t i = 0; text[i] != '\0' && replacements < max_replacements; ++i) {
        if (text[i] == ' ' || text[i] == ',' || text[i] == '.') {
            text[i] = ':';
            ++replacements;
        }
    }

    return replacements;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t max_replacements;

    if (scanf("%zu", &max_replacements) != 1) {
        fputs("Invalid replacement count.\n", stderr);
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (ch == EOF) {
        fputs("Missing input text.\n", stderr);
        return EXIT_FAILURE;
    }

    ssize_t length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input text.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    replace_delimiters(line, max_replacements);

    if (puts(line) == EOF) {
        free(line);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}