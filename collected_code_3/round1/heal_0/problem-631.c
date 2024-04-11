#include <stdio.h>
#include <string.h>

void replace_spaces_and_underscores(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ')
            str[i] = '_';
        else if(str[i] == '_')
            str[i] = ' ';
    }
}

int main() {
    char str[] = "Hello_World This_is_a_test";
    replace_spaces_and_underscores(str);
    printf("%s\n", str);
    return 0;
}