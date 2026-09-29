#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *source, char replacement)
{
    char *result;
    size_t length;
    size_t i;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = source[i] == ' ' ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    char input[1024];
    char replacement;
    char *result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (scanf(" %c", &replacement) != 1) {
        fputs("Failed to read the replacement character.\n", stderr);
        return EXIT_FAILURE;
    }

    result = replace_spaces(input, replacement);
    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}