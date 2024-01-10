#include <stdio.h>
#include <string.h>

char findFirstNonRepeatedCharacter(char *str) {
    if(str == NULL) {
        return '\0';
    }
    
    int len = strlen(str);
    char count[256] = {0};
    int i;

    for (i = 0; i < len; i++) {
        count[str[i]]++;
    }

    for (i = 0; i < len; i++) {
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