#include<stdio.h>

int asciiValue(char c) {
    return (int) c;
}

int main() {
    char character;
    printf("Enter a character: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'character' is initialized [premium-bughuntingUninit]
     */
    scanf("%c", &character);
    printf("ASCII value of %c is %d", character, asciiValue(character));
    return 0;
}