#include <stdio.h>

char findFirstNonRepeatedCharacter(char *str) {
    char count[256] = {0};
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        count[str[i]]++;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (count[str[i]] == 1) {
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