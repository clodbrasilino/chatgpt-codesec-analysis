#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str)
{
    size_t len;
    size_t out_index = 0;
    size_t i;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    result = malloc(2 * len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];

        if (isupper(c)) {
            if (out_index > 0) {
                result[out_index++] = '_';
            }
            result[out_index++] = (char)tolower(c);
        } else {
            result[out_index++] = (char)c;
        }
    }

    result[out_index] = '\0';
    return result;
}

int main(void)
{
    const char *input = "camelCaseString";
    char *output = camel_to_snake(input);

    if (output == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    free(output);

    return EXIT_SUCCESS;
}