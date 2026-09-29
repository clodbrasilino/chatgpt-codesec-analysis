#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_characters(const char *source, size_t source_length,
                        const char *characters, size_t characters_length)
{
    unsigned char remove_set[UCHAR_MAX + 1U] = {0};
    size_t write_index = 0U;

    if ((source == NULL && source_length != 0U) ||
        (characters == NULL && characters_length != 0U) ||
        source_length == SIZE_MAX) {
        return NULL;
    }

    for (size_t i = 0U; i < characters_length; ++i) {
        remove_set[(unsigned char)characters[i]] = 1U;
    }

    char *result = malloc(source_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < source_length; ++i) {
        unsigned char current = (unsigned char)source[i];

        if (remove_set[current] == 0U) {
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

    char *result = remove_characters(source, sizeof source - 1U,
                                     characters, sizeof characters - 1U);
    if (result == NULL) {
        fputs("Failed to remove characters.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    if (printf("%s\n", result) < 0) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}