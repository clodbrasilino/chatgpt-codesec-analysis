#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str) {
    if (str == NULL) {
        return '\0';
    }
  
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    if(len >= MAX_SIZE) {
        return '\0';
    }
  
    unsigned int count[MAX_SIZE] = {0};
  
    for (size_t i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }
   
    for (size_t i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = "abacddbec";
    char result = findFirstNonRepeatedCharacter(str);

    printf("First non-repeated character: %c\n", result);

    return 0;
}