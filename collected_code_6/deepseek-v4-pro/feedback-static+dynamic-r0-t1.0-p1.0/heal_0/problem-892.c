#include <stdio.h>
#include <ctype.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *src = str;
    char *dst = str;
    int in_space = 0;
    
    while (*src != '\0') {
        if (isspace((unsigned char)*src)) {
            if (!in_space) {
                *dst = ' ';
                dst++;
                in_space = 1;
            }
            src++;
        } else {
            *dst = *src;
            dst++;
            src++;
            in_space = 0;
        }
    }
    
    *dst = '\0';
}

int main(void) {
    char str1[] = "Hello   World";
    char str2[] = "   Multiple   spaces   in   string   ";
    char str3[] = "NoSpacesHere";
    char str4[] = "";
    char str5[] = "   ";
    
    printf("Original: \"%s\"\n", str1);
    remove_multiple_spaces(str1);
    printf("Modified: \"%s\"\n\n", str1);
    
    printf("Original: \"%s\"\n", str2);
    remove_multiple_spaces(str2);
    printf("Modified: \"%s\"\n\n", str2);
    
    printf("Original: \"%s\"\n", str3);
    remove_multiple_spaces(str3);
    printf("Modified: \"%s\"\n\n", str3);
    
    printf("Original: \"%s\"\n", str4);
    remove_multiple_spaces(str4);
    printf("Modified: \"%s\"\n\n", str4);
    
    printf("Original: \"%s\"\n", str5);
    remove_multiple_spaces(str5);
    printf("Modified: \"%s\"\n\n", str5);
    
    return 0;
}