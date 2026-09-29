#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_odd_characters(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t j = 0;

    for (size_t i = 0; i < len; i += 2) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "abcdefgh";
    
    printf("Original string: %s\n", str);
    
    remove_odd_characters(str);
    
    printf("Modified string: %s\n", str);
    
    return 0;
}