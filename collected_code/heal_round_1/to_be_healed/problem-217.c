#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char findFirstRepeatedChar(char* str) {
    int count[256] = {0}; // Assuming ASCII characters
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    int length = strlen(str);
    
    for (int i = 0; i < length; i++) {
        count[str[i]]++;
        if (count[str[i]] > 1) {
            return str[i];
        }
    }
    
    return '\0'; // No repeated characters found
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