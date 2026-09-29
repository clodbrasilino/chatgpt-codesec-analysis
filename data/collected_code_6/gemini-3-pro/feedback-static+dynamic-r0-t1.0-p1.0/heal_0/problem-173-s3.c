#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void filter_alphanumeric(char *str) {
    if (str == NULL) {
        return;
    }

    char *src = str;
    char *dst = str;

    while (*src != '\0') {
        if (isalnum((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    char test_str[] = "Hello, World! 123 @#$";
    
    filter_alphanumeric(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}