#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **split_into_characters(const char *string, size_t *count)
{
    char **characters;
    size_t length;
    size_t index;

    if (string == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    length = strlen(string);

    if (length == 0 || length > SIZE_MAX / sizeof(*characters)) {
        return NULL;
    }

    characters = calloc(length, sizeof(*characters));
    if (characters == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        characters[index] = malloc(2);
        if (characters[index] == NULL) {
            while (index > 0) {
                free(characters[--index]);
            }
            free(characters);
            return NULL;
        }

        characters[index][0] = string[index];
        characters[index][1] = '\0';
    }

    *count = length;
    return characters;
}

static void free_characters(char **characters, size_t count)
{
    size_t index;

    if (characters == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(characters[index]);
    }

    free(characters);
}

int main(void)
{
    const char input[] = "Hello";
    char **characters;
    size_t count = 0;
    size_t index;

    if (input[0] == '\0') {
        return EXIT_SUCCESS;
    }

    characters = split_into_characters(input, &count);
    if (characters == NULL) {
        fputs("Failed to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (puts(characters[index]) == EOF) {
            free_characters(characters, count);
            return EXIT_FAILURE;
        }
    }

    free_characters(characters, count);
    return EXIT_SUCCESS;
}