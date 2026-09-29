#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *camel_to_snake(const char *str, size_t str_len) {
    char *result = malloc(str_len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < str_len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char input[] = "ThisIsCamelCase";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = camel_to_snake(input, input_len);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}