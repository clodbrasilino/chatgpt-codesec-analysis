#include <string.h>
#include <stdio.h>

void replace_chars(char* str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ') {
            str[i] = '_';
        } else if(str[i] == '_') {
            str[i] = ' ';
        }
    }
}

int main() {
    char str[] = "Hello_World this is_a_test";
    replace_chars(str);
    printf("%s", str);
    return 0;
}