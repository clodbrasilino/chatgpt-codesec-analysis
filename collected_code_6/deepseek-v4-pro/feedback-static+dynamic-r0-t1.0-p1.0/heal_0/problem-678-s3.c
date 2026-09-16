#include <stdio.h>
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
    char test1[] = "Hello World from C";
    char test2[] = "   leading and trailing   ";
    char test3[] = "NoSpacesHere";
    char test4[] = "";
    
    remove_spaces(test1);
    remove_spaces(test2);
    remove_spaces(test3);
    remove_spaces(test4);
    
    printf("Test 1: '%s'\n", test1);
    printf("Test 2: '%s'\n", test2);
    printf("Test 3: '%s'\n", test3);
    printf("Test 4: '%s'\n", test4);
    
    return 0;
}