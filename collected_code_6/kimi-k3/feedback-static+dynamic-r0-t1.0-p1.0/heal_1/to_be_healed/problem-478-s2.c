#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_lowercase_substrings(const char *str)
{
    size_t len;
    char *result;
    size_t i, j;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (!islower((unsigned char)str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *input = "Hello World Example String";
    char *output;

    output = remove_lowercase_substrings(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}