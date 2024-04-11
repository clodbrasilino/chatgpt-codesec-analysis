#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char ch) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    char str[] = "Hello World!";
    char ch = '_';

    replace_spaces(str, ch);

    printf("%s\n", str);

    return 0;
}