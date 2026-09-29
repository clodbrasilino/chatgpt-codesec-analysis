#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* camel_to_snake(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int result_len = 0;
    for (int i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i]) && i > 0 && str[i-1] != '_') {
            result_len += 2;
        } else {
            result_len += 1;
        }
    }
    char *result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < len; ++i) {
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
    const char *input = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}