#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ')
            str[i] = '_';
        else if(str[i] == '_')
            str[i] = ' ';
    }
}

int main() {
    char str[] = "Hello_World";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}