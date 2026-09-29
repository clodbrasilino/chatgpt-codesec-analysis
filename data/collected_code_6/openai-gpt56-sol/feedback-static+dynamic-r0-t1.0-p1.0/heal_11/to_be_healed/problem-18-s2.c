#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_characters(const char *source, size_t source_size,
                        const char *characters, size_t characters_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char remove_set[UCHAR_MAX + 1U] = {0};
    size_t source_length = 0;
    size_t characters_length = 0;
    size_t write_index = 0;

    if (source == NULL || characters == NULL ||
        source_size == 0U || characters_size == 0U) {
        return NULL;
    }

    while (source_length < source_size && source[source_length] != '\0') {
        ++source_length;
    }

    if (source_length == source_size) {
        return NULL;
    }

    while (characters_length < characters_size &&
           characters[characters_length] != '\0') {
        ++characters_length;
    }

    if (characters_length == characters_size) {
        return NULL;
    }

    for (size_t i = 0; i < characters_length; ++i) {
        remove_set[(unsigned char)characters[i]] = 1U;
    }

    if (source_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(source_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char current = (unsigned char)source[read_index];

        if (remove_set[current] == 0U) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    const char source[] = "Hello, World!";
    const char characters[] = "lo";

    char *result = remove_characters(source, sizeof source,
                                     characters, sizeof characters);

    if (result == NULL) {
        fputs("Failed to remove characters.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}