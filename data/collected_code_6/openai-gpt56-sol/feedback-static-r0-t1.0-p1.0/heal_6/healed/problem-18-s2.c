#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_characters(const char *source, size_t source_length,
                        const char *characters, size_t characters_length)
{
    unsigned char remove_set[256] = {0};
    size_t write_index = 0;

    if (source == NULL || characters == NULL || source_length == SIZE_MAX) {
        return NULL;
    }

    for (size_t i = 0; i < characters_length; ++i) {
        remove_set[(unsigned char)characters[i]] = 1;
    }

    char *result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < source_length; ++i) {
        unsigned char current = (unsigned char)source[i];

        if (remove_set[current] == 0) {
            result[write_index++] = source[i];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    static const char source[] = "Hello, World!";
    static const char characters[] = "lo";

    char *result = remove_characters(
        source,
        sizeof source - 1,
        characters,
        sizeof characters - 1
    );

    if (result == NULL) {
        fputs("Failed to remove characters.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}