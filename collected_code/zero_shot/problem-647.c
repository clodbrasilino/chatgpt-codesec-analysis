#include <stdio.h>
#include <string.h>

void splitStringAtUppercase(char* str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "SplitThisStringAtUppercase";
    splitStringAtUppercase(str);
    return 0;
}