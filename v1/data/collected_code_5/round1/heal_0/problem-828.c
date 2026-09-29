#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countCharacters(char *str, int *alpha, int *digit, int *special) {
    int i = 0;

    while(str[i] != '\0') {
        if(isalpha(str[i])) {
            (*alpha)++;
        } else if(isdigit(str[i])) {
            (*digit)++;
        } else {
            (*special)++;
        }
        i++;
    }
}

int main() {
    char str[100];
    int alpha = 0, digit = 0, special = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    str[strcspn(str, "\n")] = 0;

    countCharacters(str, &alpha, &digit, &special);

    printf("Alphabets: %d\n", alpha);
    printf("Digits: %d\n", digit);
    printf("Special characters: %d\n", special);

    return 0;
}