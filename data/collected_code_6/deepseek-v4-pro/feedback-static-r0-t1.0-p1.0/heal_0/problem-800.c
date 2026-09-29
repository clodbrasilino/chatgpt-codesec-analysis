#include <stdio.h>
#include <ctype.h>

char *remove_whitespaces(char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    char *read = str;
    char *write = str;
    
    while (*read != '\0') {
        if (!isspace((unsigned char)*read)) {
            *write = *read;
            write++;
        }
        read++;
    }
    
    *write = '\0';
    return str;
}

int main(void) {
    char str1[] = "  Hello   World  ";
    printf("Original: \"%s\"\n", str1);
    remove_whitespaces(str1);
    printf("Modified: \"%s\"\n", str1);
    
    char str2[] = "\tTab\tand\nNewline\r\n";
    printf("Original: \"%s\"\n", str2);
    remove_whitespaces(str2);
    printf("Modified: \"%s\"\n", str2);
    
    char str3[] = "NoWhitespace";
    printf("Original: \"%s\"\n", str3);
    remove_whitespaces(str3);
    printf("Modified: \"%s\"\n", str3);
    
    return 0;
}