#include<stdio.h>

const char findCharacter(const char* str, int length) {
    char result = '\0';
    int i = 0;
    
    while(i < length && str[i] != '\0') {
        result += str[i];
        i++;
    }
    
    return result;
}

int main() {
    char str[101] = {0};
    printf("Enter a string: ");
    fgets(str, 101, stdin);
    
    char character = findCharacter(str, 101);
    printf("Character made by adding all the characters of the given string: %c\n", character);
    
    return 0;
}