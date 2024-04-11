#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countCharacters(char* str, int* alphabets, int* digits, int* special) {
    int i = 0;
    while (str[i] != '\0') {
        if (isalpha(str[i]))
            (*alphabets)++;
        else if (isdigit(str[i]))
            (*digits)++;
        else
            (*special)++;
        i++;
    }
}

int main() {
    char str[100];
    int alphabets = 0, digits = 0, special = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    countCharacters(str, &alphabets, &digits, &special);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);

    return 0;
}