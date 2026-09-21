#define _POSIX_C_SOURCE 200809L

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

static int discard_input_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch;
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

    if (discard_input_line() == EOF) {
        fprintf(stderr, "Failed to read the input string.\n");
        return EXIT_FAILURE;
    }

    if (getline(&line, &capacity, stdin) < 0) {
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