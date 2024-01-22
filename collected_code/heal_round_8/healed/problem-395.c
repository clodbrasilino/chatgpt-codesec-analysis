#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str, size_t str_length) {
    if (str == NULL || str_length >= MAX_SIZE) {
        return '\0';
    }

    unsigned int count[MAX_SIZE] = {0};

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
    char str[MAX_SIZE] = "abacddbec";
    char result = findFirstNonRepeatedCharacter(str, strlen(str));

    printf("First non-repeated character: %c\n", result);

    return 0;
}