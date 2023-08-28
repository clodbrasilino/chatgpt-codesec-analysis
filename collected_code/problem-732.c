#include <stdio.h>

void replaceCharsWithColon(char *str) {
    if (str == NULL)
        return;
        
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char str[] = "Hello, world. This is a test";
    replaceCharsWithColon(str);
    printf("%s\n", str);
    
    return 0;
}