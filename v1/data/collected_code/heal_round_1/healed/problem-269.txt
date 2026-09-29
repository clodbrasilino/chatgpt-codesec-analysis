#include<stdio.h>

int asciiValue(char c) {
    return (int) c;
}

int main() {
    char character = '\0';
    
    printf("Enter a character: ");
    scanf("%c", &character);
    printf("ASCII value of %c is %d", character, asciiValue(character));
    return 0;
}