#include <stdio.h>
#include <stdlib.h>

size_t replace_delimiters(char *str, size_t max_replacements)
{
    size_t replacements = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0' && replacements < max_replacements) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            ++replacements;
        }
        ++str;
    }

    return replacements;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t max_replacements;

    if (scanf("%zu", &max_replacements) != 1) {
        fprintf(stderr, "Failed to read the maximum replacement count.\n");
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (getline(&line, &capacity, stdin) == -1) {
        fprintf(stderr, "Failed to read the input string.\n");
        free(line);
        return EXIT_FAILURE;
    }

    replace_delimiters(line, max_replacements);

    if (fputs(line, stdout) == EOF) {
        fprintf(stderr, "Failed to write the result.\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}