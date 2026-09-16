#include <stdio.h>
#include <string.h>

char *replace_char(char *str, char old_char, char new_char) {
    if (str == NULL) {
        return NULL;
    }
    
    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == old_char) {
            *ptr = new_char;
        }
        ptr++;
    }
    
    return str;
}

int main(void) {
    char text[] = "Hello, World!";
    char old = 'o';
    char new = '0';
    
    printf("Before: %s\n", text);
    
    if (replace_char(text, old, new) != NULL) {
        printf("After:  %s\n", text);
    }
    
    return 0;
}