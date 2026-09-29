#include <stdio.h>
#include <string.h>

int matchString(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == 'a' && i + 1 < length) {
            if(str[i + 1] == 'b' && (i + 2 < length ? str[i + 2] == 'b' : 1)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    const char str[] = "abb";
    
    if(matchString(str)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}