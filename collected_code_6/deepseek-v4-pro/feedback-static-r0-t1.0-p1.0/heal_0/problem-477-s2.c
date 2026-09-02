#include <stdio.h>
#include <ctype.h>
#include <string.h>

void string_to_lower(char *str) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char str1[] = "HELLO WORLD";
    char str2[] = "MiXeD CaSe 123 !@#";
    char str3[] = "";
    
    string_to_lower(str1);
    string_to_lower(str2);
    string_to_lower(str3);
    string_to_lower(NULL);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("[%s]\n", str3);
    
    return 0;
}