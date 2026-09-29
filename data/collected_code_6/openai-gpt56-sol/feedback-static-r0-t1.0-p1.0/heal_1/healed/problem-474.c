#include <stdio.h>
#include <stdlib.h>

char *replace_characters(const char *source, size_t source_size,
                         char target, char replacement)
{
    size_t length = 0;
    char *result;

    if (source == NULL) {
        return NULL;
    }

    while (length < source_size && source[length] != '\0') {
        ++length;
    }

    if (length == source_size) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = source[i] == target ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    const char source[] = "Hello, world!";
    char *result = replace_characters(source, sizeof source, 'o', '0');

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