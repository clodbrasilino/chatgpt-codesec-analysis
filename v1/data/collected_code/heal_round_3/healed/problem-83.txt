#include<stdio.h>

const char findCharacter(const char* str, int length) {
    char result = '\0';
    int i = 0;
    while(str[i] != '\0' && i<length) {
        result += str[i];
        i++;
    }
    return result;
}

int main() {
    char str[101] = {0};
    printf("Enter a string: ");
    fgets(str, 101, stdin);
    int length = strlen(str);
    
    if(length<=100){
        char character = findCharacter(str, length);
        printf("Character made by adding all the characters of the given string: %c\n", character);
    }
    else printf("Invalid input\n");
    return 0;
}