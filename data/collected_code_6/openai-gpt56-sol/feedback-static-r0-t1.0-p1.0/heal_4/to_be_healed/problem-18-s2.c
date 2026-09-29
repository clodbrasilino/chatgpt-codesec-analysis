#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_characters(const char *source, const char *characters)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char remove_set[UCHAR_MAX + 1] = {0};
    size_t source_length;
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL) {
        return NULL;
    }

    for (const unsigned char *p = (const unsigned char *)characters;
         *p != '\0';
         ++p) {
        remove_set[*p] = 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    source_length = strlen(source);

    if (source_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char current = (unsigned char)source[read_index];

        if (remove_set[current] == 0) {
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
    char *result = remove_characters(source, characters);

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