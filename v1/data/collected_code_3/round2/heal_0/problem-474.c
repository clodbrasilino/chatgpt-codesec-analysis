#include <stdio.h>
#include <string.h>

void replace_char(char *str, char find, char replace) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == find) {
            str[i] = replace;
        }
    }
}

int main() {
    char str[] = "Hello, World!";
    replace_char(str, 'o', '0');
    printf("%s\n", str);
    return 0;
}