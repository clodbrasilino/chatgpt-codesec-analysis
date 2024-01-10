#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitStringAtUppercase(const char* str, int len) {
    if(str == NULL || len <= 0) 
        return;
        
    for(int i = 0; i < len; i++) {
        if(isupper((unsigned char) str[i])) {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "SplitThisStringAtUppercase";
    splitStringAtUppercase(str, sizeof(str)-1);
    return 0;
}