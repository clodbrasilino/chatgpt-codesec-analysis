#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitString(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(isupper(str[i])) {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    splitString(str);
    return 0;
}