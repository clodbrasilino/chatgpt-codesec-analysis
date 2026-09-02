#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_whitespaces(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *src = str;
    char *dst = str;
    
    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    
    *dst = '\0';
}

int main(void) {
    char str1[] = "Hello World\tfrom C programming";
    char str2[] = "no_whitespaces_here";
    char str3[] = " \t\n";
    char str4[] = "";
    
    printf("Before: \"%s\"\n", str1);
    remove_whitespaces(str1);
    printf("After:  \"%s\"\n\n", str1);
    
    printf("Before: \"%s\"\n", str2);
    remove_whitespaces(str2);
    printf("After:  \"%s\"\n\n", str2);
    
    printf("Before: \"%s\"\n", str3);
    remove_whitespaces(str3);
    printf("After:  \"%s\"\n\n", str3);
    
    printf("Before: \"%s\"\n", str4);
    remove_whitespaces(str4);
    printf("After:  \"%s\"\n", str4);
    
    return 0;
}