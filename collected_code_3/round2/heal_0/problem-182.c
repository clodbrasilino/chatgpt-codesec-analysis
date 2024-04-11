#include <stdio.h>
#include <ctype.h>
#include <string.h>

void findCharTypes(char *str) {
    int upper = 0, lower = 0, number = 0, special = 0;

    for(int i = 0; i < strlen(str); i++) {
        if(isupper(str[i]))
            upper++;
        else if(islower(str[i]))
            lower++;
        else if(isdigit(str[i]))
            number++;
        else
            special++;
    }

    printf("Uppercase characters: %d\n", upper);
    printf("Lowercase characters: %d\n", lower);
    printf("Numeric characters: %d\n", number);
    printf("Special characters: %d\n", special);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    findCharTypes(str);
    return 0;
}