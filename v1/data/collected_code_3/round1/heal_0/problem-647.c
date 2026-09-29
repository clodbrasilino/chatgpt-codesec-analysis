#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitStringAtUppercase(char *str) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(isupper(str[i])) {
            printf("\n%c", str[i]);
        } else {
            printf("%c", str[i]);
        }
    }
}

int main() {
    char str[] = "HelloWorldThisIsASampleString";
    splitStringAtUppercase(str);
    return 0;
}