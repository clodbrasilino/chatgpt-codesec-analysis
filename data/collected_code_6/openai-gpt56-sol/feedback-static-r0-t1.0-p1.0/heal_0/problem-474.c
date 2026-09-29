#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_characters(const char *source, char target, char replacement)
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
        result[i] = source[i] == target ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    const char source[] = "Hello, world!";
    char *result = replace_characters(source, 'o', '0');

    if (result == NULL) {
        fputs("Failed to replace characters.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}