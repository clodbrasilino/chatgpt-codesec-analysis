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
    char str[] = "Hello, World! 123 @#$";
    
    filter_alphanumeric(str);
    printf("Filtered string: %s\n", str);
    
    char *empty_str = NULL;
    filter_alphanumeric(empty_str);
    
    return EXIT_SUCCESS;
}