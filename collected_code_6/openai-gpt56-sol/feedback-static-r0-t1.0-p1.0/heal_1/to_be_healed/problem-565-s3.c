#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int split_into_characters(const char *string, char **characters, size_t *count)
{
    size_t length;
    char *result;

    if (string == NULL || characters == NULL || count == NULL) {
        return -1;
    }

    *characters = NULL;
    *count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);

    if (length == 0) {
        return 0;
    }

    result = malloc(length);
    if (result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, string, length);
    *characters = result;
    *count = length;

    return 0;
}

int main(void)
{
    const char *string = "Hello";
    char *characters = NULL;
    size_t count = 0;
    size_t index;

    if (split_into_characters(string, &characters, &count) != 0) {
        fputs("Failed to split string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (printf("%c\n", characters[index]) < 0) {
            free(characters);
            return EXIT_FAILURE;
        }
    }

    free(characters);
    return EXIT_SUCCESS;
}