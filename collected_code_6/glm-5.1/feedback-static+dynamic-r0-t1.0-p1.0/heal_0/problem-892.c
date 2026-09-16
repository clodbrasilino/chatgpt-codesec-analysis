#include <stdio.h>
#include <stdlib.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    char *src = str;
    int space_flag = 0;

    while (*src != '\0') {
        if (*src == ' ') {
            if (!space_flag) {
                *dst++ = *src;
                space_flag = 1;
            }
        } else {
            *dst++ = *src;
            space_flag = 0;
        }
        src++;
    }

    *dst = '\0';
}

int main(void) {
    char str[] = "This   is  a   string   with    multiple    spaces.";
    
    printf("Original: \"%s\"\n", str);
    
    remove_multiple_spaces(str);
    
    printf("Modified: \"%s\"\n", str);

    return 0;
}