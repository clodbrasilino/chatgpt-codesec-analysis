#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitString(char *str) {
    int i;
    for(i = 0; i < strlen(str); i++) {
        if(islower(str[i])) {
            printf("\n");
        } else {
            printf("%c", str[i]);
        }
    }
}

int main() {
    char str[] = "HelloWorld";
    splitString(str);
    return 0;
}