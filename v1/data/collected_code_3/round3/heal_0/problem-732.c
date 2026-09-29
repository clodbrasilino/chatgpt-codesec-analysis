#include <stdio.h>
#include <string.h>

void replaceChars(char *str) {
    int i;
    for(i = 0; str[i]; i++) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replaceChars(str);
    printf("%s\n", str);
    return 0;
}