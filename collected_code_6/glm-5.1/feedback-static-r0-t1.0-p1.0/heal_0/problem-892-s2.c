#include <stdio.h>
#include <stdlib.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    char *src = str;

    while (*src != '\0') {
        *dst++ = *src++;
        if (*(src - 1) == ' ') {
            while (*src == ' ') {
                src++;
            }
        }
    }
    *dst = '\0';
}

int main(void) {
    char str[] = "This   is   a    string   with    multiple    spaces.";
    
    printf("Original: \"%s\"\n", str);
    
    remove_multiple_spaces(str);
    
    printf("Modified: \"%s\"\n", str);
    
    return 0;
}