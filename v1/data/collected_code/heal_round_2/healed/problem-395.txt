#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str) {
    if(str == NULL) {
        return '\0';
    }
    
    size_t len = strlen(str);
    if(len > MAX_SIZE) {
        return '\0';
    }

    unsigned char count[MAX_SIZE] = {0};
    size_t i;

    for (i = 0; str[i] != '\0' && i < MAX_SIZE; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (i = 0; str[i] != '\0' && i < MAX_SIZE; i++) {
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