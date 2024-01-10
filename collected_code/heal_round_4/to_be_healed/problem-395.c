#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str) {
    if(str == NULL) {
        return '\0';
    }
    
    size_t len = strnlen(str, MAX_SIZE);
    if(len >= MAX_SIZE) {
        return '\0';
    }

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    unsigned char count[MAX_SIZE] = {0};
    size_t i;

    for (i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

int main() {
    char str[] = "abacddbec";
    char result = findFirstNonRepeatedCharacter(str);

    printf("First non-repeated character: %c\n", result);

    return 0;
}