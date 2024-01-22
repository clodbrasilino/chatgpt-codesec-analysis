#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str) {
    if(str == NULL) {
        return '\0';
    }

    int str_length = strnlen(str, MAX_SIZE);
    if(str_length >= MAX_SIZE) {
        return '\0';
    }

    unsigned char count[MAX_SIZE] = {0};

    for (size_t i = 0; i < str_length; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (size_t i = 0; i < str_length; i++) {
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