#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_characters(const char *source, char target, char replacement)
{
    char *result;
    size_t length;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, source, length + 1U);

    for (size_t i = 0U; i < length; ++i) {
        if (result[i] == target) {
            result[i] = replacement;
        }
    }

    return result;
}

int main(void)
{
    const char input[] = "Hello, world!";
    char *result = replace_characters(input, 'o', '0');

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