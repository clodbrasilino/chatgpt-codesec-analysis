#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_with_colon(const char *str) {
    size_t len;
    char *result;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            result[i] = ':';
        } else {
            result[i] = str[i];
        }
    }

    result[len] = '\0';

    return result;
}

int main(void) {
    const char *input = "hello world, this.is a test";
    char *output;
    int ret;

    output = replace_with_colon(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);

    ret = EXIT_SUCCESS;

    return ret;
}