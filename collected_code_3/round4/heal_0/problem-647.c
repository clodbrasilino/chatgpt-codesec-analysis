#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitStringAtUppercase(char *str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        if(isupper(str[i])) {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    splitStringAtUppercase(str);
    return 0;
}