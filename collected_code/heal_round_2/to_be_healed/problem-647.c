#include <stdio.h>
#include <string.h>
#include <ctype.h>

void splitStringAtUppercase(const char* str) {
    if(str == NULL) 
        return;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
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