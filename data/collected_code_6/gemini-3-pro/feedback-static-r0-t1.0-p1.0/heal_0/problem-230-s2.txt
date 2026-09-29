#include <stdio.h>

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
    char text[] = "Replace all the spaces in this string";
    
    replace_spaces(text, '-');
    
    printf("%s\n", text);
    
    return 0;
}