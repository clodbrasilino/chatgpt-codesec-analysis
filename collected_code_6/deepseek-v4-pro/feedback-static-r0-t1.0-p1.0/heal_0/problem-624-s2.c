#include <stdio.h>
#include <ctype.h>

void string_to_upper(char *str) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char str1[] = "Hello, World!";
    char str2[] = "c programming 123";
    char str3[] = "";
    
    string_to_upper(str1);
    string_to_upper(str2);
    string_to_upper(str3);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("'%s'\n", str3);
    
    return 0;
}