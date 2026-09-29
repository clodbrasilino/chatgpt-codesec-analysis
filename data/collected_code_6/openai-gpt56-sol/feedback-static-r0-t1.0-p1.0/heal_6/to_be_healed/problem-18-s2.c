#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_characters(const char *source, size_t source_length,
                        const char *characters, size_t characters_length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char remove_set[UINT8_MAX + 1] = {0};
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL || source_length == SIZE_MAX) {
        return NULL;
    }

    for (size_t i = 0; i < characters_length; ++i) {
        remove_set[(unsigned char)characters[i]] = 1;
    }

    result = malloc(source_length + 1);
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
        sizeof(source) - 1,
        characters,
        sizeof(characters) - 1
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