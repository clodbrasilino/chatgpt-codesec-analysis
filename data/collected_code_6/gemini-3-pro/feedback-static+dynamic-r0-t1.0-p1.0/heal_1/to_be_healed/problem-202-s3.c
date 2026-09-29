#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_even_characters(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (i % 2 != 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char *str = malloc(256 * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(str, "Hello World!");
    
    remove_even_characters(str);
    
    printf("%s\n", str);
    
    free(str);
    
    return 0;
}