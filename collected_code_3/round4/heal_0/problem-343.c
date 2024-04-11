#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countDigitsAndLetters(char* str, int* digitCount, int* letterCount) {
    *digitCount = 0;
    *letterCount = 0;
    int i;

    for(i = 0; str[i] != '\0'; i++) {
        if(isdigit(str[i])) {
            (*digitCount)++;
        }
        if(isalpha(str[i])) {
            (*letterCount)++;
        }
    }
}

int main() {
    char str[100];
    int digitCount, letterCount;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    countDigitsAndLetters(str, &digitCount, &letterCount);

    printf("Number of digits: %d\n", digitCount);
    printf("Number of letters: %d\n", letterCount);

    return 0;
}