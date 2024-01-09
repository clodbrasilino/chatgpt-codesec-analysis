#include <stdio.h>

void countCharacterFrequency(char *str) {
    int count[256] = {0};
    int i;

    for(i = 0; str[i] != '\0'; i++)
        count[str[i]]++;

    for(i = 0; i < 256; i++) {
        if(count[i] != 0)
            printf("%c : %d\n", i, count[i]);
    }
}

int main() {
    char str[] = "Hello, World!";
    countCharacterFrequency(str);
    
    return 0;
}