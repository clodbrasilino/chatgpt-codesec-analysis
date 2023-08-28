#include<stdio.h>

char findCharacter(char* str) {
    char result = '\0';
    int i = 0;
    
    while(str[i] != '\0') {
        result += str[i];
        i++;
    }
    
    return result;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    
    char character = findCharacter(str);
    printf("Character made by adding all the characters of the given string: %c\n", character);
    
    return 0;
}