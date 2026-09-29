#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_spaces(char *str) {
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
    char test1[] = "Hello World";
    char test2[] = "  Leading and trailing  ";
    char test3[] = "NoSpacesHere";
    char test4[] = "   ";
    char test5[] = "";
    
    remove_spaces(test1);
    remove_spaces(test2);
    remove_spaces(test3);
    remove_spaces(test4);
    remove_spaces(test5);
    
    printf("'%s'\n", test1);
    printf("'%s'\n", test2);
    printf("'%s'\n", test3);
    printf("'%s'\n", test4);
    printf("'%s'\n", test5);
    
    return 0;
}