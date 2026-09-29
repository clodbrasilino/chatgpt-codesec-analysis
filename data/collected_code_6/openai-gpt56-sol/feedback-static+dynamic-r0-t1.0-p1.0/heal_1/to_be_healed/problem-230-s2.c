#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *input, char replacement)
{
    char *result;
    size_t length;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);
    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = input[i] == ' ' ? replacement : input[i];
    }
    result[length] = '\0';

    return result;
}

int main(void)
{
    const char input[] = "Replace blank spaces safely";
    char *result = replace_spaces(input, '_');

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}