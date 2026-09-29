#include <stdio.h>
#include <string.h>

char findFirstRepeatedChar(const char* str) {
    int count[256] = {0}; 
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
    
    for (int i = 0; i < length; i++) {
        count[str[i]]++;
        if (count[str[i]] > 1) {
            return str[i];
        }
    }
    
    return '\0'; 
}

int main() {
    char str[] = "hello world";
    char firstRepeatedChar = findFirstRepeatedChar(str);
    
    if (firstRepeatedChar != '\0') {
        printf("The first repeated character is: %c\n", firstRepeatedChar);
    } else {
        printf("No repeated characters found\n");
    }
    
    return 0;
}