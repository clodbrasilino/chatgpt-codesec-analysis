#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    int i;
    for(i = 0; str[i]; i++) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char str[] = "Hello, world. This is a test.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}