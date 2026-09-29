#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitStringAtUppercase(const char* str) {
    if(str == NULL) 
        return;
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(isupper((unsigned char) str[i])) {
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