#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if (*str == ' ') {
            *str = replacement;
        }
        str++;
    }
}

int main(void) {
    char *text = NULL;
    size_t size = 100;
    
    text = (char *)malloc(size * sizeof(char));
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(text, "Hello World! This is a test string.", size - 1);
    text[size - 1] = '\0';

    printf("Original: %s\n", text);
    
    replace_spaces(text, '-');
    
    printf("Replaced: %s\n", text);

    free(text);
    text = NULL;

    return 0;
}