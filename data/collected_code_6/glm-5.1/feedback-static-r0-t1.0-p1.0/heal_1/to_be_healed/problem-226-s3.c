#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklm";
    char *output = remove_odd_index(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}