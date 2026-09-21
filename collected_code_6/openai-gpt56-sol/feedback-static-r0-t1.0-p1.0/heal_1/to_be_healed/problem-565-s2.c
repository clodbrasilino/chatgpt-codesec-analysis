#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_into_characters(const char *string, size_t *count)
{
    char **characters;
    size_t length;
    size_t i;

    if (string == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);

    if (length == 0) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(*characters)) {
        return NULL;
    }

    characters = calloc(length, sizeof(*characters));
    if (characters == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        characters[i] = malloc(2);
        if (characters[i] == NULL) {
            while (i > 0) {
                free(characters[--i]);
            }
            free(characters);
            return NULL;
        }

        characters[i][0] = string[i];
        characters[i][1] = '\0';
    }

    *count = length;
    return characters;
}

void free_characters(char **characters, size_t count)
{
    size_t i;

    if (characters == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(characters[i]);
    }

    free(characters);
}

int main(void)
{
    const char input[] = "Hello";
    char **characters;
    size_t count;
    size_t i;

    characters = split_into_characters(input, &count);
    if (characters == NULL) {
        /* Possible weaknesses found:
         *  Condition 'input[0]=='\0'' is always false [knownConditionTrueFalse]
         */
        if (input[0] == '\0') {
            return EXIT_SUCCESS;
        }

        fputs("Failed to split string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(characters[i]) == EOF) {
            free_characters(characters, count);
            return EXIT_FAILURE;
        }
    }

    free_characters(characters, count);
    return EXIT_SUCCESS;
}