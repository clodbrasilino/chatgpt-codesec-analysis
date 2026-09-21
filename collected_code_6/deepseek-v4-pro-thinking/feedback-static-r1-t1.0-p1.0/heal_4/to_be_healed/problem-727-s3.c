#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *remove_non_alphanumeric(const char *input)
{
    size_t len;
    size_t alnum_count;
    size_t i;
    char *result;
    size_t out;

    if (input == NULL)
        return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    alnum_count = 0;
    for (i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i]))
            alnum_count++;
    }

    result = malloc(alnum_count + 1);
    if (result == NULL)
        return NULL;

    out = 0;
    for (i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[out++] = input[i];
        }
    }
    result[out] = '\0';

    return result;
}

int main(void)
{
    char *cleaned = remove_non_alphanumeric("Hello, World! 123");
    if (cleaned != NULL) {
        puts(cleaned);
        free(cleaned);
    }
    return 0;
}