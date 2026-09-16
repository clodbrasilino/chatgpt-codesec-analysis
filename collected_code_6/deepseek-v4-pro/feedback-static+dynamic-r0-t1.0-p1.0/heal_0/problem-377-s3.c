#include <stdio.h>
#include <string.h>

void remove_char(char *str, char ch) {
    char *src = str;
    char *dst = str;
    
    while (*src) {
        if (*src != ch) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    char str[] = "Hello, World!";
    char ch = 'o';
    
    printf("Original string: %s\n", str);
    remove_char(str, ch);
    printf("After removing '%c': %s\n", ch, str);
    
    return 0;
}