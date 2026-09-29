#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_char(const char* str, char find, char replace) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* str_copy = (char*)malloc(len + 1);
    
    if (str_copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        if (str[i] == find) {
            str_copy[i] = replace;
        } else {
            str_copy[i] = str[i];
        }
    }

    return str_copy;
}

int main(void) {
    const char* original = "hello world";
    char* modified = replace_char(original, 'o', '0');

    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        printf("Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}