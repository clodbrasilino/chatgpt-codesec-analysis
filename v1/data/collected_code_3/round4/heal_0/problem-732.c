#include <stdio.h>
#include <string.h>

void replaceChars(char *str) {
    int i = 0;
    while(str[i]) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
        i++;
    }
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replaceChars(str);
    printf("%s\n", str);
    return 0;
}