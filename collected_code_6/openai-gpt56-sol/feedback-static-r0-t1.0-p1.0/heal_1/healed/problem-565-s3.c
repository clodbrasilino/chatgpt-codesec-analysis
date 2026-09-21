#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int split_into_characters(const char *string, size_t string_size,
                          char **characters, size_t *count)
{
    const char *terminator;
    size_t length;
    char *result;

    if (string == NULL || characters == NULL || count == NULL) {
        return -1;
    }

    *characters = NULL;
    *count = 0;

    terminator = memchr(string, '\0', string_size);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - string);
    if (length == 0) {
        return 0;
    }

    result = malloc(length);
    if (result == NULL) {
        return -1;
    }

    memcpy(result, string, length);

    *characters = result;
    *count = length;

    return 0;
}

int main(void)
{
    static const char string[] = "Hello";
    char *characters = NULL;
    size_t count = 0;

    if (split_into_characters(string, sizeof string, &characters, &count) != 0) {
        fputs("Failed to split string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (printf("%c\n", characters[index]) < 0) {
            free(characters);
            return EXIT_FAILURE;
        }
    }

    free(characters);
    return EXIT_SUCCESS;
}